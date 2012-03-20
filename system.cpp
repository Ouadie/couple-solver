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

void my_system::bind_force(string f, string p) {
  tuple act;
  act.point = p;
  act.force = f;
  actions.push_back(act);
}

string my_system::list_actions() {
  stringstream out;
  out << "   force at point" << endl;
  vector<tuple>::iterator it = actions.begin();
  for (int i = 0; it < actions.end(); i++, it++) {
    out << i << ": " << it->force << " at " << it->point << endl;
  }
  return out.str();
}

force_vector my_system::force_equ() {
  vector<tuple>::iterator it = actions.begin();
  force_vector result = forces[it->force];
  it++;
  for (it; it < actions.end(); it++) {
    result += forces[it->force]; 
  }
  return result;
}

force_vector my_system::moment_equ(point loc) {
  vector<tuple>::iterator it = actions.begin();
  action act(points[it->point], forces[it->force]);
  force_vector result =  act.moment_at(loc);
  it++;
  for (it; it < actions.end(); it++) {
    act = action(points[it->point], forces[it->force]);
    result += act.moment_at(loc);
  }
  // sum all couples as well
  map<string, force_vector>::iterator itr = couples.begin();
  for (int i = 0; i < couples.size(); i++, itr++) {
    result += itr->second;
  }
  return result;
}

#endif
