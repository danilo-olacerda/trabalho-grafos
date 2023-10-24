#include <stdlib.h>
#include <string>
#include "Node.h"

Node::Node(int id)
{
  this.id = id;
  idHash = id % Graph::getNNodeHash();

  next = NULL;

  adjList = new Node()[nAdjHash];
  for (int i; i < adjList; i++)
  {
    adjList[i] = NULL;
  }
}

int Node::getId()
{
  return id;
}