#include <cmath>
#include "../include/Solution.h"

Solution::Solution(Graph *g, int routeNumber, double capacityTruck)
{
  cout << capacityTruck << "Variavel não está sendo usada";
  this->g = g;
  order = g->getOrder();
  this->routeNumber = routeNumber;
  Route *route = new Route(routeNumber);
  for (int i = 0; i < 4; ++i)
  {
    route[i] = Route(routeNumber);
  }

  distances = new double *[order];
  for (int i = 0; i < order; ++i)
  {
    distances[i] = new double[order];
  }

  int i = 0, j = 0;
  Item<Node> *itemNodeOuter = g->getNodes()->getFirstItem();
  while (itemNodeOuter != NULL)
  {
    Item<Node> *itemNodeInner = g->getNodes()->getFirstItem();
    while (itemNodeInner != NULL)
    {
      double *posI = itemNodeOuter->getData()->getPos();
      double *posJ = itemNodeInner->getData()->getPos();
      distances[i][j] = sqrt(pow(posI[0] - posJ[0], 2) + pow(posI[1] - posJ[1], 2));

      itemNodeInner = g->getNodes()->getNextItem(itemNodeInner);
      j++;
    }

    itemNodeOuter = g->getNodes()->getNextItem(itemNodeOuter);
    i++;
  }
}

Solution::~Solution()
{
  for (int i = 0; i < order; ++i)
  {
    delete[] distances[i];
  }
  delete[] distances;

  for (int i = 0; i < order; i++)
  {
    // delete routes[i];
  }
  delete[] routes;
}

Route *Solution::getRoutes()
{
  return routes;
}