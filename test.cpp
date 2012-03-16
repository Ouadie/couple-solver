#include <iostream>
#include "force_vector.h"
#include "system.h"

using namespace std;

int main(void) {
  system sys;
  force_vector force;
  point loc;
  sys.forces["a"] = force;
  cout << sys.forces["a"];
  return 0;
}
