#include <stdlib.h>
#include "../include/Node.h"

Node::Node(int label)
{
  this->label = label;
  forwardEdges = new HashTable<Edge>(4);
  backwardEdges = new HashTable<Edge>(4);
  weight = 1.0;
  inDegree = 0;
  outDegree = 0;
  in = -1;
  out = -1;
  predecessor = NULL;
}

Node::~Node()
{
  delete forwardEdges;
  delete backwardEdges;
}

int Node::getLabel()
{
  return label;
}

HashTable<Edge> *Node::getForwardEdges()
{
  return forwardEdges;
}

int Node::getIn()
{
  return in;
}
void Node::setIn(int value)
{
  in = value;
}

int Node::getOut()
{
  return out;
}

void Node::setOut(int value)
{
  out = value;
}

Node *Node::getPredecessor()
{
  return predecessor;
}

void Node::setPredecessor(Node *predecessor)
{
  this->predecessor = predecessor;
}

void Node::addEdge(int neighbor, Node *neighborPointer, bool isForward)
{
  Edge *edge = new Edge(neighborPointer);
  if (isForward == 1)
  {
    forwardEdges->addItem(neighbor, edge);
    outDegree += 1;
  }
  else
  {
    backwardEdges->addItem(neighbor, edge);
    inDegree += 1;
  }
}

void Node::removeEdge(int neighbor, bool isForward, int *status)
{
  if (isForward == 1)
  {
    forwardEdges->removeItem(neighbor, status);
    outDegree -= 1;
  }
  else
  {
    backwardEdges->removeItem(neighbor, status);
    inDegree -= 1;
  }
  // Não conferimos o status, pois a validação feita em graph.cpp garante que o head existe
}