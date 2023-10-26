#include "stdlib.h"
#include "../include/Edge.h"

Edge::Edge(Node *headPointer)
{
  this->headPointer = headPointer;
  this->weight = 1.0;
}