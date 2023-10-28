#include "stdlib.h"
#include "../include/Edge.h"

Edge::Edge(Node *neighborPointer, float weight)
{
  this->neighborPointer = neighborPointer;
  this->weight = weight;
}

Node *Edge::getNeighborPointer()
{
  return neighborPointer;
}

float Edge::getWeight()
{
  return weight;
}