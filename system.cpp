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

void my_system::bind_force(string p, string f) {
  tuple act;
  act.first = p;
  act.second = f;
  actions.push_back(act);
}

string my_system::list_actions() {
  stringstream out;
  out << "Force  Point" << endl;
  vector<tuple>::iterator it = actions.begin();
  for (it = actions.begin(); it < actions.end(); it++) {
    out << it->first << " " << it->second << endl;
  }
  return out.str();
}

#endif
