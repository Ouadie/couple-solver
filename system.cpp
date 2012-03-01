#if !defined SYSTEM_CPP
#define SYSTEM_CPP

#include "system.h"

using namespace std;


void system::add_force(string name, force_vector force){
  if (find_force(name) != -1)
    throw "name already exists";

  force_names.push_back(name);
  forces.push_back(force);
}

int system::find_force(string name){
  for (int i = 0, length = force_names.size(); i < length; i++) {
    if (name == force_names[i])
      return i;
  }
  return -1;
}

void system::list_force_names() {
  for (int i = 0, length = force_names.size(); i < length; i++) {
    cout << force_names[i] << endl;
  }
}

void system::add_point(string name, point point){
  if (find_point(name) != -1)
    throw "name already exists";

  point_names.push_back(name);
  points.push_back(point);
}

int system::find_point(string name){
  for (int i = 0, length = point_names.size(); i < length; i++) {
    if (name == point_names[i])
      return i;
  }
  return -1;
}

void system::list_point_names() {
  for (int i = 0, length = point_names.size(); i < length; i++) {
    cout << point_names[i] << endl;
  }
}

#endif
