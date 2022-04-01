#define RYML_SINGLE_HDR_DEFINE_NOW

#include <octave/oct.h>
#include "ryml_all.hpp"

#include <iostream>
#include <sstream>
#include <vector>
#include <array>

octave_value decode (ryml::NodeRef node);
octave_value decode_seq (ryml::NodeRef node);
octave_value decode_map (ryml::NodeRef node);
octave_value decode_num (ryml::NodeRef node);
octave_value decode_string (ryml::NodeRef node);

bool IsUint (c4::csubstr s);
bool IsInt (c4::csubstr s);
bool IsDouble (c4::csubstr s);
bool IsBool (c4::csubstr s);
bool IsNum (c4::csubstr s);
bool IsString (c4::csubstr s);

uint GetUint (c4::csubstr s);
int GetInt (c4::csubstr s);
double GetDouble (c4::csubstr s);
bool GetBool (c4::csubstr s);
std::string GetString (c4::csubstr s);

octave_value
decode (ryml::NodeRef node)
{
  if (node.is_seq ())
    return decode_seq (node);
  else if (node.is_map ())
    return decode_map (node);
  else
  {
    c4::csubstr s = node.val ();
    
    if (IsNum (s)) 
      return decode_num (node);
    else if (IsBool (s))
      return GetBool (s);
    else if (IsString (s))
      return GetString (s);
    else
      error ("yamldecode: unidentified type.");
  }
}

octave_value
decode_seq (ryml::NodeRef node)
{
  // assume it's a numeric sequence.

  NDArray retval (dim_vector (node.num_children (), 1));
  octave_idx_type ind = 0;
  
  for (const auto& e : node)
  {
    retval (ind++) = decode_num (e).double_value ();
  }

  return retval;
}

octave_value
decode_map (ryml::NodeRef node)
{
  octave_scalar_map retval;

  for (const auto& e : node)
  {
    std::stringstream buffer;

    buffer << e.key ();
    retval.assign (buffer.str (), decode (e));
  }

  return retval;
}

octave_value
decode_num (ryml::NodeRef node)
{
  ryml::csubstr s = node.val ();

  if (IsInt (s))
    return GetInt (s);
  else if (IsDouble (s))
    return GetDouble (s);
  else
    error ("jsondecode: unidentified type");
}

bool
IsUint (c4::csubstr s)
{
  uint num_uint;

  return c4::from_chars (s, &num_uint);
}

bool
IsInt (c4::csubstr s)
{
  int num_int;

  return c4::from_chars (s, &num_int);
}

bool
IsDouble (c4::csubstr s)
{
  double num_double;

  return c4::from_chars (s, &num_double);
}

bool
IsBool (c4::csubstr s)
{
  bool num_bool;

  return c4::from_chars (s, &num_bool);
}

bool
IsString (c4::csubstr s)
{
  c4::csubstr num_string;

  return c4::from_chars (s, &num_string);
}

bool
IsNum (c4::csubstr s)
{
  return (IsDouble(s) || IsInt(s));
}

uint
GetUint (c4::csubstr s)
{
  uint num_uint;

  c4::from_chars (s, &num_uint);
  return num_uint;
}

int
GetInt (c4::csubstr s)
{
  int num_int;

  c4::from_chars (s, &num_int);
  return num_int;
}

double
GetDouble (c4::csubstr s)
{
  double num_double;

  c4::from_chars (s, &num_double);
  return num_double;
}

bool
GetBool (c4::csubstr s)
{
  bool num_bool;

  c4::from_chars (s, &num_bool);
  return num_bool;
}

std::string
GetString (c4::csubstr s)
{
  std::stringstream buffer;

  buffer << s;
  return buffer.str ();
}

DEFUN_DLD (yamldecode, args, /* nargout */,
          "[...] = yamldecode(YAML String)\n\
Decode YAML data into Octave data types.\n\
")
{
  if (args.length () != 1)
    print_usage ();

  std::string yaml = args(0).string_value ();

  if (!yaml.length ())
    error("YAML string cannot be empty.");

  ryml::Tree tree = ryml::parse_in_arena (ryml::to_csubstr (yaml));

  ryml::NodeRef root = tree.rootref ();

  return decode (root);
}