#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include "../include/Graph.hpp"

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
  Node *tailPointer = nodes->getItem(tail)->getData();
  Node *headPointer = nodes->getItem(head)->getData();
  if (tailPointer != NULL && headPointer != NULL)
  {
    tailPointer->addEdge(head, headPointer, 1);

    headPointer->addEdge(tail, tailPointer, 0);

    if (isOriented == false)
    {
      headPointer->addEdge(tail, tailPointer, 1);

      tailPointer->addEdge(head, headPointer, 0);
    }
  }

  ++nEdges;
}

void Graph::removeEdge(int tail, int head)
{
  Node *tailPointer = nodes->getItem(tail)->getData();
  Node *headPointer = nodes->getItem(head)->getData();
  if (tailPointer != NULL && headPointer != NULL)
  {
    int *status;

    tailPointer->removeEdge(head, 1, status);
    headPointer->decrementInDegree();

    headPointer->removeEdge(tail, 0, status);
    tailPointer->decrementInDegree();

    if (isOriented == false)
    {
      headPointer->removeEdge(tail, 1, status);
      tailPointer->decrementInDegree();

      tailPointer->removeEdge(head, 0, status);
      headPointer->decrementInDegree();
    }
  }

  --nEdges;
}

void Graph::dfsForTransitiveClosure(int label, bool isForward)
{
  Stack<Node> *stack = new Stack<Node>();

  stack->push(nodes->getItem(label)->getData());

  HashTable<Edge> *edges = isForward ? node->getForwardEdges() : node->getBackwardEdges();
  Item<Edge> *itemEdge = edges->getFirstItem();
  Node *current;
  Node *neighbor;
  while (!stack->isEmpty())
  {
    current = stack->pop();
    if (node->getIn() == -1)
    {
      node->setIn(1);

      while (itemEdge != NULL)
      {
        neighbor = itemEdge->getData()->getNeighborPointer();
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
      std::cout << itemNode->getData()->getLabel() << " ";
    }
    itemNode = nodes->getNextItem(itemNode);
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
      std::cout << itemNode->getData()->getLabel() << " ";
    }
    itemNode = nodes->getNextItem(itemNode);
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

  HashTable<Edge> *edges = current->getForwardEdges();
  Item<Edge> *itemEdge = edges->getFirstItem();
  Edge *edge;

  Node *current = nodes->getItem(label1)->getData();
  current->setOut(0);
  minHeap->enqueue(0, NULL, current);
  Node *destiny = nodes->getItem(label2)->getData();
  Node *neighbor;

  while (destiny->getPredecessor() == NULL)
  {
    current = minHeap->dequeue();

    current->setIn(1);

    while (itemEdge != NULL)
    {
      edge = itemEdge->getData();
      neighbor = edge->getNeighborPointer();
      float weight = edge->getWeight();
      float dist = current->getIn() + weight;

      if (neighbor->getOut() > dist)
      {
        neighbor->setOut(dist);
        neighbor->setPredecessor(current);
      }

      if (neighbor->getIn() == -1)
      {
        minHeap->enqueue(dist, current, neighbor);
      }
    }
    itemEdge = edges->getNextItem(itemEdge);
  }

  delete minHeap;

  Stack<Node> *stack = new Stack<Node>();

  while (current != NULL)
  {
    stack->push(current);
    current = current->getPredecessor();
  }

  while (!stack->isEmpty())
  {
    std::cout << stack->pop()->getLabel() << " ";
  }

  delete stack;
}

Graph::arrangePredecessors(Node *middle, Node *node1, Node *node2)
{
  Node *forwardNeighbor;
  Node *backwardNeighbor;

  forwardNeighbor = middle->getForwardEdges()->getItem(node1->getLabel());
  if (forwardNeighbor != NULL)
  {
    backwardNeighbor = middle->getBackwardEdges()->getItem(node2->getLabel());
  }
  else
  {
    forwardNeighbor = middle->getForwardEdges()->getItem(node2->getLabel());
    backwardNeighbor = middle->getBackwardEdges()->getItem(node1->getLabel());
  }
  forwardNeighbor->setPredecessor(middle);
  middle->setPredecessor(backwardNeighbor);
}

void Graph::floyd(label1, label2)
{
  MinHeap<Node> *minHeap = new MinHeap<Node>(order);

  Item<Node> *itemNode = nodes->getFirstItem();
  while (itemNode != NULL)
  {
    minHeap->enqueue(itemNode->getKey(), NULL, itemNode->getData());
  }

  Node **arrayNodes = new Node *[order];
  float **weights = new float *[order];
  for (int i = 0; i < order; ++i)
  {
    float *weightBetweenNeighbors = new float[order];
    weights[i] = weightBetweenNeighbors;

    arrayNodes[i] = minHeap->dequeue();
  }

  delete minHeap;

  HashTable<Edge> *edges;
  float weight;
  for (int i = 0; i < order; ++i)
  {
    edges = arrayNodes[i]->getForwardEdges();
    for (int j = 0; i < order; ++j)
    {
      if (i == j)
      {
        weight = 0;
      }
      else
      {
        Item<Edge> *edge = edges->getItem(arrayNodes[j]->getLabel());
        if (edge == NULL)
        {
          weight = INT_MAX;
        }
        else
        {
          weight = edge->getData()->getWeight();
        }
      }
      weights[i][j] = weight;
    }
  }

  Node *current;
  int k;
  for (int i = 0; i < order; ++i)
  {
    k = i;
    current = arrayNodes[k];
    for (int j = 0; j < order; ++j)
    {
      if (i == k || j == k || i == j)
      {
        float x = weights[i][k];
        float y = weights[k][j];

        if (weights[i][j] > x + y && x != INT_MAX && y != INT_MAX)
        {
          weights[i][j] = x + y;

          arrangePredecessors(current, arrayNodes[i], arrayNodes[j]);
        }
      }
    }
  }
}

void Graph::genMinTree(Node *root)
{
  Queue<Node> *queue = new Queue<Node>();
  queue->enqueue(root);

  HashTable<Edge> *edges = current->getForwardEdges();
  Item<Edge> *itemEdge = edges->getFirstItem();
  Node *current;
  Node *currentPredecessor;
  Node *nodeAbove = NULL;
  Node *neighbor;
  int level = 0;
  cout << "Level 0:\n";
  while (!queue->isEmpty())
  {
    current = queue->dequeue();

    currentPredecessor = current->getPredecessor();
    if (nodeAbove != currentPredecessor)
    {
      cout << "Level " << ++level << ":\n";
      nodeAbove = currentPredecessor;
    }

    if (currentPredecessor != NULL)
    {
      cout << currentPredecessor->getLabel();
    }
    else
    {
      cout << "NULL"
    }
    cout << " -> " << current->getLabel() << "\n";

    while (itemEdge != NULL)
    {
      neighbor = itemEdge->getData()->getNeighborPointer();
      if (neighbor->getIn() == 1 && neighbor->getPredecessor() == current)
      {
        queue->enqueue(neighbor);
      }
    }
  }

  delete queue;
}

void Graph::prim(int *nodeLabels)
{
  if (isOriented)
  {
    return;
  }

  MinHeap<Node> *minHeap = new MinHeap<Node>(nEdges);

  Node *current;
  int n = sizeof(nodeLabels) / sizeof(int);
  for (int i = 1; i < n; ++i)
  {
    current = nodes->getItem(nodeLabels[i])->getData();
    current->setIn(0);
    current->setOut(INT_MAX)
  }
  current = nodes->getItem(nodeLabels[0])->getData();
  current->setIn(0);
  current->setOut(0);
  minHeap->enqueue(0, NULL, current);
  Node *root = current;

  HashTable<Edge> *edges;
  Item<Edge> *itemEdge;
  Edge *edge;
  Node *neighbor;
  int i = 0;
  while (true)
  {
    current = minHeap->dequeue();

    current->setIn(1);
    if (++i >= n)
    {
      break;
    }

    edges = current->getForwardEdges();
    itemEdge = edges->getFirstItem();
    while (itemEdge != NULL)
    {
      edge = itemEdge->getData();
      float weight = edge->getWeight();
      neighbor = edge->getNeighborPointer();
      if (neighbor->getIn() == 0 && neighbor->getOut() > weight)
      {
        neighbor->setOut(weight);
        neighbor->setPredecessor(current);
        if (neighbor->getIn() == 0)
        {
          minHeap->enqueue(weight, current, neighbor);
        }
      }
      itemEdge = edges->getNextItem(itemEdge);
    }
  }

  delete minHeap;

  genMinTree(root);
}

void Graph::kruskal(int *nodeLabels)
{
  if (isOriented)
  {
    return;
  }

  MinHeap<Node> *minHeap = new MinHeap<Node>(nEdges);

  HashTable<Edge> *edges;
  Item<Edge> *itemEdge;
  Edge *edge;
  Node *current;
  Node *neighbor;
  int n = sizeof(nodeLabels) / sizeof(int);
  for (int i = 1; i < n; ++i)
  {
    current = nodes->getItem(nodeLabels[i])->getData();
    current->setIn(0);
    edges = current->getForwardEdges();
    for (itemEdge = edges->getFirstItem(); itemEdge != NULL; itemEdge = edges->getNextItem(itemEdge))
    {
      edge = itemEdge->getData();
      float weight = edge->getWeight();
      neighbor = edge->getNeighborPointer();

      neighbor->setPredecessor(current);

      minHeap->enqueue(weight, current, neighbor);
    }
  }

  Node *root;

  int i = 0;
  while (i < n)
  {
    current = minHeap->dequeue();

    if (current->getIn() == 0)
    {
      current->setIn(1);
      if (++i == 1)
      {
        current->setPredecessor(NULL);
        root = current
      }
    }
  }

  delete minHeap;

  genMinTree(root);
}

void Graph::generateTree(int label)
{
  Stack<Node> *stack = new Stack<Node>();

  Node *current = nodes->getItem(label)->getData();
  stack->push(current);

  HashTable<Edge> *edges = current->getForwardEdges();
  Item<Edge> *itemEdge = edges->getFirstItem();
  Node *neighbor;
  while (!stack->isEmpty())
  {
    current = stack->pop();
    if (node->getIn() == -1)
    {
      node->setIn(1);
      stack->push(current);

      while (itemEdge != NULL)
      {
        neighbor = itemEdge->getData()->getNeighborPointer();
        if (neighbor->getIn() == -1)
        {
          neighbor->setPredecessor(current);
          stack->push(neighbor);
        }
        itemEdge = edges->getNextItem(itemEdge);
      }
    }
  }

  delete stack;

  Queue<Node> *queue = new Queue<Node>();
  Queue<Node> *returnEdgeQueue = new Queue<Node>();

  queue->enqueue(current);

  Node *currentPredecessor;
  Node *nodeAbove = NULL;
  int level = 0;
  cout << "Level 0:\n";
  while (!queue->isEmpty())
  {
    current = queue->dequeue();
    currentPredecessor = current->getPredecessor();

    if (nodeAbove != currentPredecessor)
    {
      cout << "Level " << ++level << ":\n";
      nodeAbove = currentPredecessor;

      Node *node = returnEdgeQueue->dequeue();
      while (nodeAbove == node->getPredecessor())
      {
        cout << nodeAbove->getLabel() << " <- " << node->getLabel();
        node = returnEdgeQueue->dequeue();
      }
    }

    if (nodeAbove == NULL)
    {
      cout << "NULL";
    }
    else
    {
      cout << nodeAbove->getLabel()
    }
    cout << " -> " << current;

    edges = current->getForwardEdges();
    itemEdge = edges->getFirstItem();
    Node *neighbor;
    while (itemEdge != NULL)
    {
      neighbor = itemEdge->getData()->getNeighborPointer();
      if (neighbor->getPredecessor() == nodeAbove)
      {
        queue->enqueue(neighbor);
      }
      else
      {
        returnEdgeQueue->enqueue(neighbor);
      }
      itemEdge = edges->getNextItem(itemEdge);
    }
  }

  delete queue;
}

void Graph::topologicalSort()
{
  if (!isOriented)
  {
    return;
  }

  Stack<Node> *sort = new Stack<Node>();
  Stack<Node> *stack = new Stack<Node>();

  Node *node = nodes->getFirstItem()->getData();
  Node *current;
  while (node != NULL)
  {
    if (node->getIn() == -1)
    {
      stack->push(nodes->getFirstItem()->getData());

      HashTable<Edge> *edges = node->getForwardEdges();
      Item<Edge> *itemEdge = edges->getFirstItem();
      Node *neighbor;
      while (!stack->isEmpty())
      {
        current = stack->pop();
        if (current->getIn() == -1)
        {
          current->setIn(1);
          stack->push(current);

          while (itemEdge != NULL)
          {
            neighbor = itemEdge->getData()->getNeighborPointer();
            if (neighbor->getIn() == -1)
            {
              stack->push(neighbor);
            }

            itemEdge = edges->getNextItem(itemEdge);
          }
        }
        else if (current->getOut() == -1)
        {
          sort->push(current);
        }
      }
    }
    node = nodes->getNextItem(node);
  }

  delete stack;

  while (!sort->isEmpty())
  {
    cout << sort->pop()->getLabel() << " ";
  }

  delete sort;
}
