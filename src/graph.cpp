#include <stdlib.h>
#include "Graph.h"

Graph::Graph(bool isOriented)
{
  nodes = new HashTable<Node>();

  order = 0;
  nEdges = 0;
  this->isOriented = isOriented;
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
  Node *node = new Node();
  nodes->addItem(label, node);
  ++order;
}

void Graph::removeNode(int label)
{
  int status;
  nodes->removeItem(label, &status);
  if (status == 0)
  {
    --order;
  }
}

void Graph::addEdge(int tail, int head)
{
  Node *tailPointer = nodes->getItem(tail)->data;
  Node *headPointer = nodes->getItem(head)->data;
  if (tailPointer != NULL && headPointer != NULL)
  {
    tailPointer->addEdge(head, headPointer);
    headPointer->incrementInDegree();
    if (isOriented == 0)
    {
      headPointer->addEdge(tail, tailPointer);
      tailPointer->incrementInDegree();
    }
    ++nEdges;
  }
}

void Graph::removeEdge(int tail, int head)
{
  Node *tailPointer = nodes->getItem(tail)->data;
  Node *headPointer = nodes->getItem(head)->data;
  if (tailPointer != NULL && headPointer != NULL)
  {
    int status;
    tailPointer->removeEdge(head, &status);
    headPointer->decrementInDegree();
    if (isOriented == 0)
    {
      headPointer->removeEdge(tail, &status);
      tailPointer->decrementInDegree();
    }
    --nEdges;
  }
}

void Graph::directTransitiveClosure(int label)
{
  if (isOriented == 0)
  {
    return;
  }

  Item<Node> item = nodes->getItem(label);
  int *set = new int[order - 1]; // order - 1 = tamanho máximo do vetor
}