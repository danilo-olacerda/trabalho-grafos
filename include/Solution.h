#ifndef SOLUTION_H
#define SOLUTION_H

#include "Graph.h"
#include "Route.h"

class Solution
{
private:
  Graph *g;
  int order;
  int routeNumber;
  Route *routes;
  double **distances;

public:
  Solution(Graph *g, int routeNumber, double capacityTruck);
  ~Solution();

  Route *getRoutes();
};

#endif // SOLUTION_H