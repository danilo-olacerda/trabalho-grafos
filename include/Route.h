#ifndef ROUTE_H
#define ROUTE_H

#include "DataStructures/Queue.h"

class Route
{
private:
  Queue<int> route;
  int capacity;

public:
  Route(int capacity);
};

#endif // ROUTE_H