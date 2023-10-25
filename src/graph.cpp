#include <stdlib.h>
#include <string>
#include "Graph.h"
#include "HashTable.h"

Graph::Graph(int order)
{
  nodes = new HashTable<Node>;

  this->order = order;
  nEdges = 0;
}

int Graph::getOrder()
{
  return order;
}

int Graph::getNEdges()
{
  return nEdges;
}

void Graph::InsertNode(int id)
{
}

void Graph::removeNode(int id)
{
}