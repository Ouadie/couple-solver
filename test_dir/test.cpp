#include<iostream>
#include<map>

#include "hash.cpp"

using namespace std;

int main () {
  my_hash<int> myobject;
  myobject["a"] = 1;
  cout << myobject["a"] << endl;
  cout << myobject << endl;
  return 0;
}

