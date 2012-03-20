#if !defined POINT_CPP
#define POINT_CPP

#include "point.h"

using namespace std;

point::point() {
  x = 0; y = 0; z = 0;
}

point::point(double p_x, double p_y, double p_z){
  x = p_x;
  y = p_y;
  z = p_z;
}

double point::lengthTo(const point &rhs) const{
  return pow(pow(x - rhs.x, 2) + pow(y - rhs.y, 2) + pow(z - rhs.z, 2), 0.5);
}

point point::operator-(const point &rhs) const {
  return point(rhs.x - x, rhs.y - y, rhs.z - z);
}

ostream& operator<<(ostream& out, const point &rhs) {
  return out << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
}


#endif
