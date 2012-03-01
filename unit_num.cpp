/************************************************\
* unit_num.cpp                        vector add *
* Caleb Everett                          statics *
*                                                *
* applies units to values, and provides the      *
* to convert between them                        *
\************************************************/
#if !defined UNIT_NUM_CPP
#define UNIT_NUM_CPP

#include "unit_num.h"

using namespace std;

// default value is 0 N
unit_num::unit_num () {
  value = 0;
  unit = "N";
}

// new unit_num with p_value and p_unit
unit_num::unit_num (double p_value, string p_unit){
  if (Convert.toN(p_unit) == 0) { // unit conversion not found
    throw p_unit; // hacky exception handaling, return the string of the illegal unit
  }
  value = p_value;
  unit = p_unit;
}

// converts to p_unit
void unit_num::change_unit (string p_unit) {
  if (Convert.toN(p_unit) == 0) { // unit conversion not found
    throw p_unit; // hacky exception handaling, return the string of the illegal unit
  }
  value = value * Convert.toN(unit); // convert current value to newtons
  unit = p_unit;
  value = value / Convert.toN(unit); // convert back to new unit
}

// math presrving units
unit_num& unit_num::operator+=(const unit_num& rhs) {
  value += (rhs.value * Convert.toN(rhs.unit))/Convert.toN(unit); // convert rhs to newtons, then to this unit
  return *this;
}

// math presrving units
unit_num& unit_num::operator-=(const unit_num& rhs) {
  value -= (rhs.value * Convert.toN(rhs.unit))/Convert.toN(unit); // convert rhs to newtons, then to this unit
  return *this;
}

// math presrving units
unit_num unit_num::operator+(const unit_num& rhs) const {
  unit_num result(*this);
  result += rhs;
  return result;
}

// stream operator for printing
unit_num unit_num::operator-(const unit_num& rhs) const {
  unit_num result(*this);
  result -= rhs;
  return result;
}

ostream& operator<<(ostream& out, const unit_num &rhs) {
  double value = rhs.value;
  if (value < 0.0001 && value > -0.0001) value = 0;
  out.precision(3);
  return out << value << " " << rhs.unit;
}
#endif

