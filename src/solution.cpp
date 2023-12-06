#include <cmath>
#include "../include/Solution.h"

Solution::Solution(Graph *g, int routeNumber, double capacityTruck)
{
  this->g = g;
  order = g->getOrder();
  this->routeNumber = routeNumber;
  route = new Route[routeNumber];
  for (int i = 0; i < 4; ++i)
  {
    route[i] = Route(capacityTruck);
  }

  distances = new double *[order];
  for (int i = 0; i < order; ++i)
  {
    distances[i] = new double[order];
  }

  Node *itemNodeOuter = g->getNodes()->getFirstItem();
  while (itemNodeOuter != NULL)
  {
    Node *itemNodeInner = g->getNodes()->getFirstItem();
    while (itemNodeInner != NULL)
    {
      float posI = itemNodeOuter->getPos();
      float posJ = itemNodeInner->getPos();
      distances[i][j] = sqrt(pow(posI[0] - posJ[0], 2) + pow(posI[1] - posJ[1], 2));

      Node *itemNodeInner = g->getNodes()->getNextItem(itemNodeInner);
    }

    itemNodeOuter = g->getNodes()->getNextItem(itemNodeOuter);
  }
}

Solution::~Solution()
{
  for (int i = 0; i < order; ++i)
  {
    delete[] distances[i];
  }
  delete[] distances;

  for (int i = 0; i < ; i++)
  {
    delete routes[i];
  }
  delete[] routes;
}

Route *Solution::getRoutes()
{
}