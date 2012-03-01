/**************************************\
* force_vector.h           vector adder *
* Caleb everett                statics *
*                                      *
* defines force_vector class and vector *
* exception                            *
\**************************************/
#if !defined FORCE_VECTOR_H
#define FORCE_VECTOR_H

#define PI 3.14159265

#include <iostream>
#include <exception>
#include <sstream>
#include <math.h>
#include "unit_num.h"

using namespace std;

class nullVectorException: public exception {
  virtual const char* what() const throw() {
    return "the distance between the points given cannot be zero";
  }
};

class illegalAngleException: public exception {
  virtual const char* what() const throw() {
    return "The angles provided were illegal, angles must be between 0 and 180";
  }
};

class force_vector{
  public:
    unit_num i;
    unit_num j;
    unit_num k;
    force_vector();
    force_vector(double i_v, string i_u, double j_v, string j_u, double k_v, string k_u);
    force_vector(unit_num &i_p, unit_num &j_p, unit_num &k_p);
    force_vector(double mag, string unit, double x1, double y1, double z1, double x2, double y2, double z2);
    force_vector(double mag, string unit, double alpha, double beta, double gama);
    void change_unit(string) throw (string);
    unit_num magnitude() const;
    string unit() const;
    string toCartesian() const;
    string to_coord_dir() const;
    force_vector& operator+=(const force_vector &rhs);
    force_vector& operator-=(const force_vector &rhs);
    force_vector operator+(const force_vector &rhs) const;
    force_vector operator-(const force_vector &rhs) const;
    friend ostream& operator<<(ostream& out, const force_vector &rhs);
};
#endif

