#include "stdlib.h"
#include "../include/Edge.h"

Edge::Edge(Node *neighborPointer)
{
  this->neighborPointer = neighborPointer;
  this->weight = 1.0;
}

Node *Edge::getNeighborPointer()
{
  return neighborPointer;
}