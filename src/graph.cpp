#include <stdlib.h>
#include "Graph.h"

Graph::Graph(int order)
{
  nodes = new HashTable<Node>;

  this->order = order;
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
  nodes->removeItem(id);
}