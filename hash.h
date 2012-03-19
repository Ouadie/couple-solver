#if !defined HASH_H
#define HASH_H

#include <iostream>
#include <sstream>
#include <map>

using namespace std;

template <class T>
class hash {
  private:
    map<string, T> _map;
  public:
    T& operator[] (string x);
    string to_string() {
      stringstream out;
      typename map<string, T>::iterator it;
      for (it=_map.begin(); it != _map.end(); it++) {
        out << it->first << ": " << it->second << endl;
      }
      return out.str();
    }

    //friend ostream& operator<<(ostream& out, const hash<T> &rhs)
    //  { return out << rhs.to_string(); }
};

#endif

