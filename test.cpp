#include <iostream>
#include "hash.h"
#include "force_vector.h"
#include "system.h"

using namespace std;

int main () {
  my_system sys;
  sys.forces["1"] = force_vector(0, "N", 1, "N", 0, "N");
  sys.forces["2"] = force_vector(0, "N",  -1, "N", 0, "N");
  sys.forces["3"] = force_vector (0, "N",  1, "N", 0, "N");

  sys.points["O"]= point(0,0,0);
  sys.points["a"]= point(1,0,0);
  sys.points["b"]= point(-1,0,0);

  sys.bind_force("1", "a");
  sys.bind_force("2", "b");
  sys.bind_force("3", "O");

  cout << sys.list_actions() << endl;
  cout << sys.force_equ() << endl;
  cout << sys.moment_equ(sys.points["O"]) << endl;
  cout << sys.moment_equ(sys.points["a"]) << endl;
  cout << sys.moment_equ(sys.points["b"]) << endl;

  sys = my_system();
  sys.forces["3"] = force_vector (0, "N",  1, "N", 0, "N");
  sys.couples["1"] = force_vector (0, "N", 0, "N", 2, "N");

  sys.points["O"]= point(0,0,0);
  sys.points["a"]= point(1,0,0);
  sys.points["b"]= point(-1,0,0);

  sys.bind_force("3", "O");

  cout << sys.list_actions() << endl;
  cout << sys.force_equ() << endl;
  cout << sys.moment_equ(sys.points["O"]) << endl;
  cout << sys.moment_equ(sys.points["a"]) << endl;
  cout << sys.moment_equ(sys.points["b"]) << endl;
  return 0;
}
  
