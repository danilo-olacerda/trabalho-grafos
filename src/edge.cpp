#include "stdlib.h"
#include "../include/Edge.hpp"

Edge::Edge(Node *neighborPointer)
{
  this->neighborPointer = neighborPointer;
  weight = 1.0;
}

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