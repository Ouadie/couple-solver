#include <iostream>
#include "hash.h"

using namespace std;

int main () {
  my_hash<int> tmp;
  tmp["a"] = 1;
  tmp["b"] = 5;
  tmp["c"] = 2;
  cout << tmp << endl;

  my_hash<string> tmp2;
  tmp2["a"] = "big test";
  tmp2["djh"] = "ddd test";
  tmp2["adf"] = "that test";
  tmp2["a"] = "more test";
  cout << tmp2 << endl;
  return 0;
}
  
