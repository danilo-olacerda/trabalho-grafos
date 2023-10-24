#include <stdlib.h>
#include <string>
#include "Node.h"

Node::Node(int id)
{
  this.id = id;
  next = NULL;
}

int Node::getId()
{
  return id;
}