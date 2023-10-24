#include <stdlib.h>
#include <string>
#include "Graph.h"

Graph::Graph(int order)
{
  this->order = order;
  nEdges = 0;

  nodeList = new Node()[nNodeHash];
  for (int i; i < nNodeHash; i++)
  {
    nodeList[i] = NULL;
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

int Graph::getnNodeHash()
{
  return nNodeHash;
}

void Graph::InsertNode(int id)
{
  Node node = new Node(id);
  int idHash = node->idHash;
  node->next = nodeList[idHash];
  nodeList[idHash] = node;
  order++;
}

void Graph::removeNode(int id)
{
  Node p = hash[getHash(id)];

  for (p; p->next != NULL; p = p->next)
  {
    if (p->next->id == id)
    {
      Node temp = p->next->next;
      delete p->next;
      p->next = temp;
      order--;
    }
  }
}