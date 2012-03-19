/*****************************************************\
* numerical.cpp                          vector adder *
* Caleb Everett                               statics *
* simple class to determine if a string is a number   *
* TODO add more units lb                              *
\*****************************************************/
#if !defined NUMERICAL_CPP
#define NUMERICAL_CPP

#include "numerical.h"

using namespace std;

// returns true if string is numerical (all charecters are digites or decimal)
bool numerical(string test) {
  if (test.find_first_not_of("0123456789.-") == test.npos) { // are there only digets, decimals or negative signs?
    int first = test.find_first_of("."); // yup, test if only one decimal
    return (test.find_first_of(".", first + 1) == test.npos); // only found one '.' test is a number
  } else
    return false; // nope were out
}

#endif
