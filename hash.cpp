#if !defined HASH_CPP
#define HASH_CPP

#include "hash.h"

using namespace std;

template <class T>
T& hash::operator[](string x) {
  return _map[x];
}


#endif
