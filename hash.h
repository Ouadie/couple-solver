#if !defined HASH_H
#define HASH_H

#include <vector>
#include <iostream>
using namespace std;

template <class T>
class hash {
  public:
    void add(string key, T value);
    int  where(string key);
    T    at(int index);
    void list(void);
  private:
    vector<T> values;
    vector<string> keys;
};

#endif

