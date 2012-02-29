/*****************************************************\
* convert.h                              vector adder *
* Caleb Everett                               statics *
* simple class to provide a means of converting units *
* TODO add more units lb                              *
\*****************************************************/
#if !defined CONVERT_CPP
#define CONVERT_CPP

#include "convert.h"

using namespace std;

// standard output for unknown unit error, make sure to update this when new units are added
string convert::unknown_unit(string unit) {
  stringstream result;
  result << "Did not recognise unit " << unit << ". Try one of the following kN, N, lb.";
  return result.str();
}

// returns the ratio between given unit and newtons
double convert::toN (string test) {
  if (test == "N")
    return 1;
  else if (test == "kN")
    return 1000;
  else if (test == "lb")
    return 4.44822162;
  else
    return 0; // zero marks that the unit was unknown
}


#endif
