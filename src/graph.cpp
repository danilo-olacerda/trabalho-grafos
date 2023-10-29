#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include "../include/Graph.h"

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
  Node *node = new Node(label);
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
        ++nEdges;
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
        ++nEdges;
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
        --nEdges;
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
        --nEdges;
      }
    }

    --nEdges;
  }
}

void Graph::dfsWithPeriodAndPrecedencyRegister(int label)
{
  Stack<Node> *stack = new Stack<Node>();

  int period = -1;
  stack->push(nodes->getItem(label)->getData());
  while (!stack->isEmpty)
  {
    Node *node = stack->pop();
    if (node->getIn() == -1)
    {
      node->setIn(++period);
      stack->push(node);

      HashTable<Edge> *edges = node->getEdges();
      Item<Edge> *itemEdge = edges->getFirstItem();
      while (itemEdge != NULL)
      {
        Node *neighbor = itemEdge->getData()->getNeighborPointer();
        if (neighbor->getIn() == -1)
        {
          neighbor->setPredecessor(node);
          stack->push(neighbor);
        }

        itemEdge = edges->getNextItem(itemEdge);
      }
    }
    else if (node->getOut() == -1)
    {
      node->setOut(++period);
    }
  }

  delete stack;
}

void Graph::dfs(int label)
{
  Stack<Node> *stack = new Stack<Node>();

  stack->push(nodes->getItem(label)->getData());
  while (!stack->isEmpty)
  {
    Node *node = stack->pop();
    if (node->getIn() == -1)
    {
      node->setIn(1);

      HashTable<Edge> *edges = node->getEdges();
      Item<Edge> *itemEdge = edges->getFirstItem();
      while (itemEdge != NULL)
      {
        Node *neighbor = itemEdge->getData()->getNeighborPointer();
        if (neighbor->getIn() == -1)
        {
          stack->push(neighbor);
        }

        itemEdge = edges->getNextItem(itemEdge);
      }
    }
  }

  delete stack;
}

void Graph::transitiveClosure(int label)
{
  dfs(label);

  Item<Node> *itemNode = nodes->getFirstItem();
  while (itemNode != NULL)
  {
    if (itemNode->getData()->getIn() == 1)
    {
      std::cout << itemNode->getData()->getKey() << " ";
    }
  }
}

void Graph::dijkstra(int label1, int label2)
{
  MinHeap<Node> *minHeap = new MinHeap<Node>(nEdges);

  Item<Node> *itemNode = nodes->getFirstItem();
  while (itemNode != NULL)
  {
    itemNode->getData()->setOut(INT_MAX);
    itemNode = nodes->getNextItem(itemNode);
  }
  Node *current = nodes->getItem(label1)->getData();
  current->setOut(0);
  minHeap->queue(0, NULL, current);

  Node *destiny = nodes->getItem(label2)->getData();
  while (destiny->getPredecessor() == NULL)
  {
    current = minHeap->unqueue();
    if (current->getIn() == -1)
    {
      current->setIn(1);

      HashTable<Edge> *edges = current->getEdges();
      Item<Edge> *itemEdge = edges->getFirstItem();
      while (itemEdge != NULL)
      {
        Edge *edge = itemEdge->getData();
        Node *neighbor = edge->getNeighborPointer();
        if (neighbor->getIn() == -1)
        {
          float weight = edge->getWeight();
          float dist = current->getIn() + weight;
          neighbor->setOut(dist);

          minHeap->queue(dist, current, neighbor);
        }

        itemEdge = edges->getNextItem(itemEdge);
      }
    }
  }

  delete minHeap;

  Stack<Node> *stack = new Stack<Node>();

  Node *node = destiny;
  while (node != NULL)
  {
    stack->push(node);
    node = node->getPredecessor();
  }

  while (!stack->isEmpty())
  {
    std::cout << stack->pop()->getLabel() << " ";
  }

  delete stack;
}

void Graph::generateNodeTree(int label)
{
  dfsWithPeriodAndPrecedencyRegister(label);
}