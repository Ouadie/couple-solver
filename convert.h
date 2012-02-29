/*****************************************************\
* convert.h                              vector adder *
* Caleb Everett                               statics *
* simple class to provide a means of converting units *
* TODO add more units lb                              *
\*****************************************************/
#if !defined CONVERT_H
#define CONVERT_H

#include <iostream>
#include <sstream>

using namespace std;

class convert {
  public:
  // standard output for unknown unit error, make sure to update this when new units are added
  string unknown_unit(string unit);
  // returns the ratio between given unit and newtons
  double toN (string test);
};

static convert Convert;

#endif
