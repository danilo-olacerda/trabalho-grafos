#include <cmath>
#include "../include/Solution.h"
#include <vector>

using namespace std;

Solution::Solution(Graph *g, int routeNumber, double capacityTruck)
{
  this->capacityTruck = capacityTruck;
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
    // delete[] routes[i];
  }

  delete[] routes;
}

Route *Solution::getRoutes()
{
  return routes;
}

void Solution::solveCVRP(Graph *graph, double capacity)
{
  vector<vector<int>> routesParam;

  vector<int> unassignedCustomers(graph->getNumDeClientes(), 0);

  while (find(unassignedCustomers.begin(), unassignedCustomers.end(), 0) != unassignedCustomers.end())
  {
    vector<int> route;
    double currentCapacity = 0;

    int startCustomer = getRandomUnassignedCustomer(unassignedCustomers);
    route.push_back(startCustomer);
    currentCapacity += graph->getCustomerDemand(startCustomer);
    unassignedCustomers[startCustomer] = 0;

    while (currentCapacity < capacity)
    {
      int nearestCustomer = getNearestUnassignedCustomer(graph, route.back(), unassignedCustomers);
      if (nearestCustomer == -1)
      {
        break;
      }

      if (currentCapacity + graph->getCustomerDemand(nearestCustomer) <= capacity)
      {
        route.push_back(nearestCustomer);
        currentCapacity += graph->getCustomerDemand(nearestCustomer);
        unassignedCustomers[nearestCustomer] = 0;
      }
      else
      {
        break;
      }
    }

    routesParam.push_back(route);
  }

  printRoutes(routesParam);
}

int Solution::getRandomUnassignedCustomer(const vector<int> &unassignedCustomers)
{
  for (int i = 0; i < unassignedCustomers.size(); ++i)
  {
    if (unassignedCustomers[i] == 0)
    {
      return i;
    }
  }
  return -1;
}

int Solution::getNearestUnassignedCustomer(Graph *graph, int currentCustomer, const vector<int> &unassignedCustomers)
{
  int nearestCustomer = -1;
  double minDistance = INT_MAX;

  for (int i = 0; i < unassignedCustomers.size(); ++i)
  {
    if (unassignedCustomers[i] == 0)
    {
      double distance = graph->dijkstra(currentCustomer, i);
      if (distance < minDistance)
      {
        minDistance = distance;
        nearestCustomer = i;
      }
    }
  }

  return nearestCustomer;
}

void Solution::printRoutes(const vector<vector<int>> &routesParam)
{
  for (const auto &route : routesParam)
  {
    cout << "Rota: ";
    for (int customer : route)
    {
      cout << customer << " ";
    }
    cout << endl;
  }
}