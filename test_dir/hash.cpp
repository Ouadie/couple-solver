#if !defined MY_HASH_CPP
#define MY_HASH_CPP
#include "hash.h"

using namespace std;

template <class T>
T & my_hash<T>::operator[](string x) {
  return _map[x];
}

template <class U>
ostream& operator<<(ostream& out, const my_hash<U> &rhs) {
  return out << "test"; 
}

#endif

