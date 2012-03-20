#if !defined MY_SYSTEM_H
#define MY_SYSTEM_H

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "hash.h"
#include "force_vector.h"
#include "point.h"

using namespace std;

struct tuple {
  string force;
  string point;
};

// an action describes a force at a point
class action {
  public:
    force_vector force;
    point loc;

    action(point p, force_vector f);

    force_vector moment_at(const point &p);
};

class my_system {
  public:
    vector<tuple> actions;

    my_hash<force_vector> forces;
    my_hash<force_vector> couples;
    my_hash<point> points;

    void bind_force(string p, string f); // which forces is at which point
    string list_actions();  // list bound points

    force_vector force_equ(); // sum of all forces
    force_vector moment_equ(point loc); // sum of all moments about a point
  private:
    void change_unit(string unit);
};

#endif

