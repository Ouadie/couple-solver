#if !defined SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <vector>
#include <map>
#include "force_vector.h"
#include "point.h"

using namespace std;

class free_body {
  public:
    void list_forces();
    force_vector force;
    point location;
};

class system {
  private:
    map<string, force_vector> forces;
    map<string, point> points;
};

#endif

