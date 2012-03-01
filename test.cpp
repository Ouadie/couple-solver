#include <iostream>
#include "force_vector.h"
#include "system.h"

using namespace std;

int main(void) {
  system sys;
  force_vector a = force_vector(5, "N", 5, "N", 5, "N");

  try {
    sys.add_force("b", a);
    sys.add_force("a", a);
  } catch (char const* e) {
    cout << e << endl;
  }
  sys.list_force_names();

  return 0;
}
