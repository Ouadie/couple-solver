#if !defined MY_HASH_H
#define MY_HASH_H

#include <iostream>
#include <map>

using namespace std;

template <class T>
class my_hash {
  private:
    map<string, T> _map;
  public:
    T& operator[] (string x);
};

template <class T>
T& my_hash<T>::operator[](string x) {
  return _map[x];
}
#endif

