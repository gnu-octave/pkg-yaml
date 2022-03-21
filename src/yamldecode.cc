#include <iostream>
#include <octave/oct.h>

DEFUN_DLD(yamldecode, args, /* nargout */,
          "Decode YAML data into Octave data types.")
{
  octave_stdout << "YAML decoding...\n";
  octave_value_list retval;
  return retval;
}