#include <stdlib.h>
#include "Node.h"

Node::Node(int label)
{
  this->label = label;
  edges = new HashTable<Edge>;
  inDegree = 0;
  outDegree = 0;
}

Node::~Node()
{
  delete edges;
}

void Node::addEdge(int head)
{
  Edge *edge = new Edge(label, head);
  edges->addItem(head, edge);
}

void Node::removeEdge(int head)
{
  edges->removeItem(head)
}