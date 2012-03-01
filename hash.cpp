#if !defined HASH_CPP
#define HASH_CPP

#include "hash.h"

using namespace std;

template <class T>
void hash<T>::add(string key, T value){
  if (where(key) != -1)
    throw "name already exists";

  keys.push_back(key);
  values.push_back(value);
}

template <class T>
int hash<T>::where(string key){
  for (int i = 0, length = keys.size(); i < length; i++) {
    if (key == keys[i])
      return i;
  }
  return -1;
}

template <class T>
void hash<T>::list() {
  for (int i = 0, length = keys.size(); i < length; i++) {
    cout << keys[i] << "\t\t" << values[i] << endl;
  }
}

#endif

