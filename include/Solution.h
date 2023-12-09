#ifndef SOLUTION_H
#define SOLUTION_H

#include "Graph.h"
#include "Route.h"
#include <vector>

#include <iostream>

using namespace std;

class Solution
{
private:
  Graph *g;
  int order;
  int routeNumber;
  Route *routes;
  double **distances;
  double capacityTruck;

public:
  Solution(Graph *g, int routeNumber, double capacityTruck);
  ~Solution();
  
  double getCargoCapacity() { return capacityTruck; }
  void solveCVRP(Graph *graph, double capacity);
  void printRoutes(const vector<vector<int>>& routes);
  int getRandomUnassignedCustomer(const vector<int>& unassignedCustomers);
  int getNearestUnassignedCustomer(Graph *graph, int currentCustomer, const vector<int> &unassignedCustomers);
  
  Route *getRoutes();
};

#endif // SOLUTION_H