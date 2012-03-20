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
    int size() { return _map.size(); }
    typename map<string, T>::iterator begin();
    typename map<string, T>::iterator end();
    T& operator[] (string x);
    template <class U>
    friend ostream& operator<<(ostream& out, my_hash<U> &rhs);
};

template <class T>
typename map<string, T>::iterator my_hash<T>::begin() {
  return _map.begin();
}

template <class T>
typename map<string, T>::iterator my_hash<T>::end() {
  return _map.end();
}

template <class T>
T& my_hash<T>::operator[](string x) {
  return _map[x];
}

template <class U>
ostream& operator<<(ostream& out, my_hash<U> &rhs) {
  if (rhs._map.size() != 0) {
    typename map<string, U>::iterator it = rhs._map.begin();
    // _map.begin and _map.end were being dicks, but this works
    for (int i = 0, len = rhs._map.size(); i < len; i++, it++) {
      out << it->first << ": " << it->second << endl;
    }
  } else {
    out << "None" << endl;
  }
  return out;
}
#endif

