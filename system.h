#if !defined SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <vector>
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
  public:
    void add_force(string name, force_vector force);
    int find_force(string name);
    void list_force_names();
    void add_point(string name, point point);
    int find_point(string name);
    void list_point_names();
  private:
    vector<force_vector> forces;
    vector<string> force_names;
    vector<point> points;
    vector<string> point_names;
    vector<free_body> free_bodies;
};

#endif

