#if !defined MY_SYSTEM_H
#define MY_SYSTEM_H

#include <iostream>
#include "hash.h"
#include "force_vector.h"
#include "point.h"

using namespace std;

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
    my_hash<action> actions;

    my_hash<force_vector> forces;
    my_hash<force_vector> moments;
    my_hash<point> points;

    force_vector force_equ(); // sum of all forces
    force_vector moment_equ(point loc); // sum of all moments about a point
  private:
    void change_unit(string unit);
};

#endif

