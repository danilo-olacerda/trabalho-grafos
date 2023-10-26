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
  int status;
  nodes->removeItem(id, &status);
  if (status == 0)
  {
    --order;
  }
}

void Graph::addEdge(int tail, int head)
{
  Node *tailPointer = nodes->getData(tail);
  Node *headPointer = nodes->getData(head);
  if (tailPointer != NULL && headPointer != NULL)
  {
    tailPointer->addEdge(head, headPointer);
    headPointer->incrementInDegree();
    ++nEdges;
  }
}

void Graph::removeEdge(int tail, int head)
{
  Node *tailPointer = nodes->getData(tail);
  Node *headPointer = nodes->getData(head);
  if (tailPointer != NULL && headPointer != NULL)
  {
    int status;
    tailPointer->removeEdge(head, &status);
    headPointer->decrementInDegree();
    --nEdges;
  }
}