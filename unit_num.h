/****************************************\
* unit_num.h                             *
* Caleb Everett                          *
*                                        *
* class for doing math on united values  *
\****************************************/
#if !defined UNIT_H
#define UNIT_H

#include <iostream>
#include <exception>
#include "convert.h"

using namespace std;

class unit_num {
  public:
    unit_num ();
    unit_num (double p_value, string p_unit);
    double change_unit (string p_unit);
    string getUnit () const {return unit;};
    void changevalue (double p_value) { value = p_value;};
    double getValue () const { return value; };
    unit_num& operator+=(const unit_num &rhs);
    unit_num& operator-=(const unit_num &rhs);
    unit_num operator+(const unit_num &rhs) const;
    unit_num operator-(const unit_num &rhs) const;

    // truncates number to 3 places
    friend ostream& operator<<(ostream& out, const unit_num &rhs);
  private:
    string unit;
    double value;
};


#endif

