#include <stdlib.h>
#include "Node.h"

Node::Node()
{
  edges = new HashTable<Edge>(4);
  inDegree = 0;
  outDegree = 0;
  in = -1;
  out = -1;
}

Node::~Node()
{
  delete edges;
}

HashTable<Edge> *Node::getEdges()
{
  return edges;
}

int Node::getIn()
{
  return in;
}
void Node::setIn(int phase)
{
  in = phase;
}

int Node::getOut()
{
  return out;
}

void Node::setOut(int phase)
{
  out = phase;
}

void Node::incrementInDegree()
{
  inDegree += 1;
}

void Node::decrementInDegree()
{
  inDegree -= 1;
}

void Node::addEdge(int neighbor, Node *neighborPointer)
{
  Edge *edge = new Edge(neighborPointer);
  edges->addItem(neighbor, edge);
  outDegree += 1;
  // o incrementInDegree do head foi feito no graph.cpp
}

void Node::removeEdge(int neighbor, int *status)
{
  edges->removeItem(neighbor, status);
  outDegree -= 1;
  // Não conferimos o status, pois a validação feita em graph.cpp garante que o head existe
  // o decrementInDegree do head foi feito no graph.cpp
}