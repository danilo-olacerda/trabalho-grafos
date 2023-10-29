#include <stdlib.h>
#include "../include/Node.h"

Node::Node(int label)
{
  this->label = label;
  edges = new HashTable<Edge>(4);
  weight = 1.0;
  inDegree = 0;
  outDegree = 0;
  in = -1;
  out = -1;
  predecessor = NULL;
}

Node::Node(int label, float weight)
{
  this->label = label;
  edges = new HashTable<Edge>(4);
  this->weight = weight;
  inDegree = 0;
  outDegree = 0;
  in = -1;
  out = -1;
  predecessor = NULL;
}

Node::~Node()
{
  delete edges;
}

int Node::getLabel()
{
  return label;
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

Item<Node> *Node::getPredecessor()
{
  return predecessor;
}

void Node::setPredecessor(Item<Node> *predecessor)
{
  this->predecessor = predecessor;
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