#include <iostream>
#include "hash.h"

using namespace std;

int main () {
  my_hash<int> tmp;
  tmp["a"] = 1;
  cout << tmp["a"] << endl;
  return 0;
}
  
