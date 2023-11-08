#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include "../include/Graph.h"

Graph::Graph(bool isOriented)
{
  nodes = new HashTable<Node>(4);
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
    tailPointer->addForwardEdge(head, headPointer, 1);

    headPointer->addBackwardEdge(tail, tailPointer, 0);

    if (isOriented == false)
    {
      headPointer->addForwardEdge(tail, tailPointer, 1);

      tailPointer->addBackwardEdge(head, headPointer, 0);
    }
  }

  ++nEdges;
}

void Graph::removeEdge(int tail, int head)
{
  Node *tailPointer = nodes->getItem(tail)->data;
  Node *headPointer = nodes->getItem(head)->data;
  if (tailPointer != NULL && headPointer != NULL)
  {
    tailPointer->removeEdge(head, 1);
    headPointer->decrementInDegree();

    headPointer->removeEdge(tail, 0);
    tailPointer->decrementInDegree();

    if (isOriented == false)
    {
      headPointer->removeEdge(tail, 1);
      tailPointer->decrementInDegree();

      tailPointer->removeEdge(head, 0);
      headPointer->decrementInDegree();
    }
  }

  --nEdges;
}

void Graph::dfsForTransitiveClosure(int label, bool isForward)
{
  Stack<Node> *stack = new Stack<Node>();

  stack->push(nodes->getItem(label)->getData());
  while (!stack->isEmpty)
  {
    Node *node = stack->pop();
    if (node->getIn() == -1)
    {
      node->setIn(1);

      HashTable<Edge> *edges = isForward ? node->getForwardEdges() : node->getBackWardEdges();
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

void Graph::directTransitiveClosure(int label)
{
  dfsForTransitiveClosure(label, 1);

  Item<Node> *itemNode = nodes->getFirstItem();
  while (itemNode != NULL)
  {
    if (itemNode->getData()->getIn() == 1)
    {
      std::cout << itemNode->getData()->getKey() << " ";
    }
  }
}

void Graph::indirectTransitiveClosure(int label)
{
  dfsForTransitiveClosure(label, 0);

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

      HashTable<Edge> *edges = current->getForwardEdges();
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

void Graph::topologicalSort()
{
  Stack<Node> *stack = new Stack<Node>();
  Stack<Node> *sort = new Stack<Node>();

  Node *current = nodes->getFirstItem()->getData();
  while (current != NULL)
  {
    if (current->getIn() == -1)
    {
      Stack<Node> *stack = new Stack<Node>();

      stack->push(nodes->getFirstItem()->getData());
      while (!stack->isEmpty)
      {
        Node *node = stack->pop();
        if (node->getIn() == -1)
        {
          node->setIn(1);
          stack->push(node);

          HashTable<Edge> *edges = node->getForwardEdges();
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
        else if (node->getOut() == -1)
        {
          sort->push(node);
        }
      }

      delete stack;
    }

    while (!sort->isEmpty())
    {
      cout << sort->pop()->getLabel() << " ";
    }
  }
}

void Graph::generateNodeTree(int label)
{
  Stack<Node> *stack = new Stack<Node>();

  int step = -1;
  stack->push(nodes->getItem(label)->getData());
  while (!stack->isEmpty)
  {
    Node *node = stack->pop();
    if (node->getIn() == -1)
    {
      node->setIn(++step);
      stack->push(node);

      HashTable<Edge> *edges = node->getForwardEdges();
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
      node->setOut(++step);
    }
  }

  delete stack;
}