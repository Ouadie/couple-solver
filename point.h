/****************************************\
* unit.h                                 *
* Caleb Everett                          *
*                                        *
* class for doing math on united values  *
\****************************************/
#if !defined POINT_H
#define POINT_H

#include <iostream>
#include <math.h>

using namespace std;

class point{
  public:
    point();
    point(double,double,double);
    double x;
    double y;
    double z;
    double lengthTo(const point &rhs) const;

    friend ostream& operator<<(ostream& out, const point &rhs);
};

#endif
