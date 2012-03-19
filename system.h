#if !defined SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include "hash.h"
#include "force_vector.h"
#include "point.h"

using namespace std;

class action {
  public:
    force_vector force;
    point location;
};

class system {
  public:
    string out_unit;
    hash<force_vector> forces;
    hash<point> points;
  private:
    void change_unit(string unit);
};

#endif

