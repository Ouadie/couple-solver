#include <iostream>
#include "hash.h"

using namespace std;

int main () {
  hash<int> force;
  force["a"] = "a";
  force.to_string();
  return 0;
}

