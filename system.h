#if !defined SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <vector>
#include "force_vector.h"
#include "point.h"
#include "hash.h"

using namespace std;

class free_body {
  public:
    void list_forces();
    force_vector force;
    point location;
};

class system {
  private:
    hash<point> points;
    hash<force_vector> forces;
};

#endif

