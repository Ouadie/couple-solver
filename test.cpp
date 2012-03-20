#include <iostream>
#include "hash.h"
#include "force_vector.h"
#include "system.h"

using namespace std;

int main () {
  my_system sys;
  force_vector one(-1, "N", 0, "N", 0, "N");
  point o(0,0,0);
  sys.bind_force("one", "o");
  cout << sys.list_actions() << endl;
  return 0;
}
  
