/********************************************\
* force_vector.cpp               vector_adder *
* Caleb Everett                      statics *
*                                            *
* methods for manipulating and representing  *
* force vectors                              *
\********************************************/
#if !defined FORCE_VECTOR_CPP
#define FORCE_VECTOR_CPP

#include "force_vector.h"

using namespace std;

// create a default vector
// { 0Ni, 0Nj, 0Nk }
force_vector::force_vector() {
  i = unit_num();
  j = unit_num();
  k = unit_num();
}

// create a vector with the given cartesian values
force_vector::force_vector(double i_v, string i_u,
    double j_v, string j_u, 
    double k_v, string k_u) {
  i = unit_num(i_v, i_u);
  j = unit_num(j_v, j_u);
  k = unit_num(k_v, k_u);
}


// vector defined by cartesian componets, that are already in unit_num format
force_vector::force_vector(unit_num &i_p, unit_num &j_p, unit_num &k_p) {
  i = i_p;
  j = j_p;
  k = k_p;
}

// vector defined as a magnatude, and a line formed by two points
// if both points are the same throws nullVectorException
force_vector::force_vector( double mag, string unit,
    double x1, double y1, double z1, 
    double x2, double y2, double z2) {
  double length = pow((pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2)), 0.5);
  if ( length == 0 ) // if lenght is 0 cannot get direction of vector
    throw nullVectorException(); // throw an error
  i = unit_num(mag * (x2 - x1) / length, unit);
  j = unit_num(mag * (y2 - y1) / length, unit);
  k = unit_num(mag * (z2 - z1) / length, unit);
}



// calculates what the third coordinate angle should be when given 2 angles.
// if finding the angle is imposible throws illegalAngleException
double getThirdAngle(double a, double b) {
  double sum =  1 - pow(cos(a),2) - pow(cos(b),2);
  if (sum < 0.001 && sum > -0.001) sum = 0; // damn percision.
  if (sum < 0 ) throw illegalAngleException(); // given angles cannot be worked out
  return acos(pow(sum,0.5));
}

// vector defined as a magnatude and coordinate angles, -1 indicates that the angle was not given
force_vector::force_vector(double mag, string unit, double alpha, double beta, double gama) {
  // atleast one angle was outside of legal range
  if (alpha < -1 || alpha > 180 || beta < -1 || beta > 180 || gama < -1 || beta > 180) {
    throw illegalAngleException();
  }

  // convert inputs to radians
  if (alpha != -1) alpha *= PI/180;
  if (beta != -1) beta *= PI/180;
  if (gama != -1) gama *= PI/180;

  if (alpha == -1 && beta != -1 && gama != -1){ // alpha is not defines, the others are
    alpha = getThirdAngle(beta, gama);
  }
  else if (alpha != -1 && beta == -1 && gama != -1) { // beta is not defines, the others are
    beta = getThirdAngle(alpha, gama);
  }
  else if (alpha != -1 && beta != -1 && gama == -1) { // gama is not defines, the others are
    gama = getThirdAngle(alpha, beta);
  }
  else if (alpha != -1 && beta != -1 && gama != -1) { // all are defined
    double test = getThirdAngle(beta, alpha); // checking that the three given angles are legal.
    test = gama - test;
    if (test > 0.0001 || test < -0.0001) // double precision 
      throw illegalAngleException();
  } else {
    throw illegalAngleException();
  }
  i = unit_num(mag * cos(alpha), unit);
  j = unit_num(mag * cos(beta), unit);
  k = unit_num(mag * cos(gama), unit);
}

// converts the vector to given unit. If unit isnt understood throws the unit
// really simply/bad way to handle exceptions
void force_vector::change_unit(string unit) throw (string) {
  i.change_unit(unit);
  j.change_unit(unit);
  k.change_unit(unit);
}

// return value and unit of the magnitude. units will always be of the x component
unit_num force_vector::magnitude() const {
  unit_num t_j = j;
  unit_num t_k = k;
  t_j.change_unit(i.getUnit());
  t_k.change_unit(i.getUnit());
  return unit_num(pow(pow(i.getValue(), 2) + pow(t_j.getValue(), 2) + pow(t_k.getValue(), 2), 0.5), i.getUnit());
}

// return the x component unit
string force_vector::unit() const {
  return i.getUnit();
}

// returns a string representation of the vector in cartesian format
// ex. 5 Ni, 2 Nj, 1 Nk
string force_vector::toCartesian() const {
  stringstream result;
  result << i << "i, " << j << "j, " << k << "k";
  return result.str();
}

// returns a string representation of the vector in coordinate direction format
// ex. 5N 90 a 90 b 0 y
string force_vector::to_coord_dir() const {
  // get angle in radians
  double alpha = acos(i.getValue()/magnitude().getValue());
  double beta = acos(j.getValue()/magnitude().getValue());
  double gama = acos(k.getValue()/magnitude().getValue());

  // convert to degrees
  alpha = alpha * 180 / PI;
  beta = beta * 180 / PI;
  gama = gama * 180 / PI;

  stringstream result;
  result << magnitude() << ", a = " << alpha << ", b = " << beta << ", y = " << gama;
  return result.str();
}

// add another vector to this vector
force_vector& force_vector::operator+=(const force_vector& rhs) {
  i += rhs.i;
  j += rhs.j;
  k += rhs.k;
  return *this;
}

// subtract another vector from this vector
force_vector& force_vector::operator-=(const force_vector& rhs) {
  i -= rhs.i;
  j -= rhs.j;
  k -= rhs.k;
  return *this;
}

// add another vector to this vector, returning the result without changing either
force_vector force_vector::operator+(const force_vector& rhs) const {
  force_vector result(*this);
  result += rhs;
  return result;
}

// subtract another vector from this vector, returning the result without changing either
force_vector force_vector::operator-(const force_vector& rhs) const {
  force_vector result(*this);
  result -= rhs;
  return result;
}

// return the vector in cartisian format
ostream& operator<<(ostream& out, const force_vector &rhs) {
  return out << "{" << rhs.i << "i, " << rhs.j << "j, " << rhs.k << "k" << "}";
}

#endif

