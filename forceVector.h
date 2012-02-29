/**************************************\
* forceVector.h           vector adder *
* Caleb everett                statics *
*                                      *
* defines forceVector class and vector *
* exception                            *
\**************************************/
#if !defined FORCEVECTOR_H
#define FORCEVECTOR_H

#define PI 3.14159265

#include <iostream>
#include <exception>
#include <sstream>
#include <math.h>
#include "unit.h"

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

class forceVector{
  public:
    unitNum i;
    unitNum j;
    unitNum k;
    forceVector();
    forceVector(double i_v, string i_u, double j_v, string j_u, double k_v, string k_u);
    forceVector(unitNum &i_p, unitNum &j_p, unitNum &k_p);
    forceVector(double mag, string unit, double x1, double y1, double z1, double x2, double y2, double z2);
    forceVector(double mag, string unit, double alpha, double beta, double gama);
    void changeUnit(string) throw (string);
    unitNum magnitude() const;
    string unit() const;
    string toCartesian() const;
    string toCoordDir() const;
    forceVector& operator+=(const forceVector &rhs);
    forceVector& operator-=(const forceVector &rhs);
    forceVector operator+(const forceVector &rhs) const;
    forceVector operator-(const forceVector &rhs) const;
    friend ostream& operator<<(ostream& out, const forceVector &rhs);
};
#endif

