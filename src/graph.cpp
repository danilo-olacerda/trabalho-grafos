#include <stdlib.h>
#include "Graph.h"

Graph::Graph(bool isOriented, bool isSucessionAdj)
{
  nodes = new HashTable<Node>(4);

  order = 0;
  nEdges = 0;
  this->isOriented = isOriented;
  this->isSucessionAdj = isSucessionAdj;
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
    if (isSucessionAdj == true)
    {
      tailPointer->addEdge(head, headPointer);
      headPointer->incrementInDegree();
      if (isOriented == false)
      {
        headPointer->addEdge(tail, tailPointer);
        tailPointer->incrementInDegree();
      }
    }
    else
    {
      headPointer->addEdge(tail, tailPointer);
      tailPointer->incrementInDegree();
      if (isOriented == false)
      {
        tailPointer->addEdge(head, headPointer);
        headPointer->incrementInDegree();
      }
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
    if (isSucessionAdj == true)
    {
      tailPointer->removeEdge(head, &status);
      headPointer->decrementInDegree();
      if (isOriented == false)
      {
        headPointer->removeEdge(tail, &status);
        tailPointer->decrementInDegree();
      }
    }
    else
    {
      headPointer->removeEdge(tail, &status);
      tailPointer->decrementInDegree();
      if (isOriented == false)
      {
        tailPointer->removeEdge(head, &status);
        headPointer->decrementInDegree();
      }
    }

    --nEdges;
  }
}

void Graph::depthSearch(int label)
{
  Stack<Node> *stack = new Stack();

  stack->push(nodes->getItem(label));

  while (!stack->isEmpty)
  {
    Node *node = stack->pop();
    if (node->getIn() == -1)
    {
      node->setIn(0);

      HashTable<Edge> *edges = node->getEdges();
      Item<Edge> edge = edges->getFirstItem();
      while (edge != NULL)
      {
      }
    }
  }
}

void Graph::transitiveClosure(int label)
{
  if (isOriented == false)
  {
    return;
  }
}