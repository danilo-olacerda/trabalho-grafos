#include <stdlib.h>
#include "Graph.h"

Graph::Graph()
{
  nodes = new HashTable<Node>;

  order = 0;
  nEdges = 0;
}

Graph::~Graph()
{
  delete nodes;
}

int Graph::getOrder()
{
  return order;
}

int Graph::getNEdges()
{
  return nEdges;
}

void Graph::addNode(int label)
{
  Node *node = new Node(label);
  nodes->addItem(label, node);
  ++order;
}

void Graph::removeNode(int id)
{
  u_int8_t status;
  nodes->removeItem(id, &status);
  if (status == 0)
    --order;
}