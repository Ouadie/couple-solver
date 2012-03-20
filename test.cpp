#include <iostream>
#include "hash.h"
#include "force_vector.h"
#include "system.h"

using namespace std;

int main () {
  force_vector one(-1, "N", 0, "N", 0, "N");
  point o(0,0,0);
  point a(1,0,0);
  point b(0,1,0);
  action a_1(a, one);
  action b_1(b, one);
  cout << a_1.moment_at(o) << endl;
  cout << b_1.moment_at(o) << endl;
  return 0;
}
  
