#if !defined SYSTEM_CPP
#define SYSTEM_CPP

#include "system.h"

using namespace std;

action::action(point p, force_vector f) {
  loc = p;
  force = f;
}

force_vector action::moment_at(const point &p) {
  point r = p - loc; 
  string unit = force.k.getUnit();
  double i = force.i.change_unit(unit),
         j = force.j.change_unit(unit),
         k = force.k.change_unit(unit);
   
  force_vector moment( 
      (r.y * k) - (r.z * j), unit,    // i 
      -((r.z * i) - (r.x * k)), unit, // j
      (r.x * j) - (r.y * i), unit     // k
      );
  return moment;
}


#endif
