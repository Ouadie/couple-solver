#if !defined SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <vector>
#include <map>
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
    map<string, force_vector> forces;
    map<string, point> points;
};

#endif

