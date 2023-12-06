#include "stdlib.h"
#include "../include/Route.h"

Solution::Solution(Graph *g, int routeNumber, float capacityTruck)
{
  this->g = g;
  this->routeNumber = routeNumber;
  this->truckNumber = truckNumber;
  this->capacityTruck = capacityTruck;
}

float **get