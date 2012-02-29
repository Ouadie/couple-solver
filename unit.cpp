/************************************************\
* unit.cpp                            vector add *
* Caleb Everett                          statics *
*                                                *
* applies units to values, and provides the      *
* to convert between them                        *
\************************************************/
#if !defined UNIT_CPP
#define UNIT_CPP

#include "unit.h"

using namespace std;

// default value is 0 N
unitNum::unitNum () {
  value = 0;
  unit = "N";
}

// new unitNum with p_value and p_unit
unitNum::unitNum (double p_value, string p_unit){
  if (Convert.toN(p_unit) == 0) { // unit conversion not found
    throw p_unit; // hacky exception handaling, return the string of the illegal unit
  }
  value = p_value;
  unit = p_unit;
}

// converts to p_unit
void unitNum::changeUnit (string p_unit) {
  if (Convert.toN(p_unit) == 0) { // unit conversion not found
    throw p_unit; // hacky exception handaling, return the string of the illegal unit
  }
  value = value * Convert.toN(unit); // convert current value to newtons
  unit = p_unit;
  value = value / Convert.toN(unit); // convert back to new unit
}

// math presrving units
unitNum& unitNum::operator+=(const unitNum& rhs) {
  value += (rhs.value * Convert.toN(rhs.unit))/Convert.toN(unit); // convert rhs to newtons, then to this unit
  return *this;
}

// math presrving units
unitNum& unitNum::operator-=(const unitNum& rhs) {
  value -= (rhs.value * Convert.toN(rhs.unit))/Convert.toN(unit); // convert rhs to newtons, then to this unit
  return *this;
}

// math presrving units
unitNum unitNum::operator+(const unitNum& rhs) const {
  unitNum result(*this);
  result += rhs;
  return result;
}

// stream operator for printing
unitNum unitNum::operator-(const unitNum& rhs) const {
  unitNum result(*this);
  result -= rhs;
  return result;
}

ostream& operator<<(ostream& out, const unitNum &rhs) {
  double value = rhs.value;
  if (value < 0.0001 && value > -0.0001) value = 0;
  out.precision(3);
  return out << value << " " << rhs.unit;
}
#endif

