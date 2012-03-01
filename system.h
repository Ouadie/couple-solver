#if !defined SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <point>
#include <forceVector>

using namespace std;

class system {
  private:
    vector<forceVector> forces;
    vector<point> points;
};

class freebody {
  public:
    forceVector force;
    point point;

}

