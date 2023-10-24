#include <stdlib.h>
#include <string>
#include "Graph.h"

Graph::Graph(int order)
{
  this->order = order;
  nEdges = 0;

  hash = new Node()[nHash];
  for (int i; i < nHash; i++)
  {
    hash[i] = NULL;
  }
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
  Node node = new Node(id);
  int idHash = node->idHash;
  node->next = hash[idHash];
  hash[idHash] = node;
  order++;
}

void Graph::removeNode(int id)
{
  Node p = hash[id % nHash];

  for (p; p->next != NULL; p = p->next)
  {
    if (p->next->id == id)
    {
      Node aux = p->next->next;
      delete p->next;
      p->next = aux;
      order--;
    }
  }
}