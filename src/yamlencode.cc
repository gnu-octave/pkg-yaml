#include <iostream>
#include <octave/oct.h>

DEFUN_DLD(yamlencode, args, /* nargout */,
          "Encode Octave data types into YAML data().")
{
  octave_stdout << "YAML encoding...\n";
  octave_value_list retval;
  return retval;
}