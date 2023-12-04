#include "stdlib.h"
#include "../include/Edge.h"

Edge::Edge(Node *neighborPointer)
{
  this->neighborPointer = neighborPointer;
  weight = 1.0;
}

Edge::Edge(Node *neighborPointer, double weight)
{
  this->neighborPointer = neighborPointer;
  this->weight = weight;
}

Node *Edge::getNeighborPointer()
{
  return neighborPointer;
}

double Edge::getWeight()
{
  return weight;
}