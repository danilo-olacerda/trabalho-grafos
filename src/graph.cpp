#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include <cfloat>
#include "../include/Graph.h"
#include "../include/Node.h"
#include "../include/Edge.h"

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

HashTable<Node> *Graph::getNodes()
{
  return nodes;
}

Node *Graph::getNode(int label)
{
  return nodes->getItem(label)->getData();
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
    // int *status Ver o que é pra ser o status
    int holder = 0;
    int *status = &holder;

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

  Node *current = nodes->getItem(label)->getData();
  stack->push(current);

  Node *neighbor;
  HashTable<Edge> *edges;
  Item<Edge> *itemEdge;
  while (!stack->isEmpty())
  {
    current = stack->pop();
    if (current->getIn() == -1)
    {
      current->setIn(1);

      edges = isForward ? current->getForwardEdges() : current->getBackwardEdges();
      itemEdge = edges->getFirstItem();
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

double Graph::dijkstra(int label1, int label2)
{
  Heap<Node> *heap = new Heap<Node>(nEdges);

  Item<Node> *itemNode = nodes->getFirstItem();
  while (itemNode != NULL)
  {
    itemNode->getData()->setOut(DBL_MAX);
    itemNode = nodes->getNextItem(itemNode);
  }

  Node *current = nodes->getItem(label1)->getData();
  current->setOut(0);
  heap->insert(0, NULL, current);
  Node *destiny = nodes->getItem(label2)->getData();
  Node *neighbor;

  HashTable<Edge> *edges = current->getForwardEdges();
  Item<Edge> *itemEdge = edges->getFirstItem();
  Edge *edge;

  double totalDistance = 0;

  while (destiny->getPredecessor() == NULL)
  {
    current = heap->remove(0);

    if (current->getIn() == -1)
    {
      current->setIn(1);

      while (itemEdge != NULL)
      {
        edge = itemEdge->getData();
        neighbor = edge->getNeighborPointer();
        double weight = edge->getWeight();
        double dist = current->getIn() + weight;

        if (neighbor->getOut() > dist)
        {
          neighbor->setOut(dist);
          neighbor->setPredecessor(current);
          neighbor->setIn(-1);
        }
        heap->insert(dist, current, neighbor);

        itemEdge = edges->getNextItem(itemEdge);

        if (neighbor == destiny)
        {
          totalDistance = dist;
        }
      }
    }
  }

  delete heap;

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

  return totalDistance;
}

void Graph::floyd(int label1, int label2)
{
  cout << label1 << " " << label2 << "\n"; // Só para sumir o warning de unused variable, depois apagar e arrumar o código
  Heap<Node> *heap = new Heap<Node>(order);

  Item<Node> *itemNode = nodes->getFirstItem();
  while (itemNode != NULL)
  {
    heap->insert(itemNode->getKey(), NULL, itemNode->getData());
  }

  Node **arrayNodes = new Node *[order];
  double **weights = new double *[order];
  for (int i = 0; i < order; ++i)
  {
    weights[i] = new double[order];
    arrayNodes[i] = heap->remove(0);
  }

  delete heap;

  HashTable<Edge> *edges;
  double weight;
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
          weight = DBL_MAX;
        }
        else
        {
          weight = edge->getData()->getWeight();
        }
      }
      weights[i][j] = weight;
    }
  }

  double x, y, sum;
  for (int k = 0; k < order; ++k)
  {
    for (int i = 0; i < order; ++i)
    {
      for (int j = 0; j < order; ++j)
      {
        if (i == k || j == k || i == j)
        {
          x = weights[i][k];
          y = weights[k][j];
          sum = x + y;

          if (weights[i][j] > sum && x != DBL_MAX && y != DBL_MAX)
          {
            weights[i][j] = sum;
          }
        }
      }
    }
  }

  delete[] arrayNodes;
  for (int i = 0; i < order; ++i)
  {
    delete[] weights[i];
  }
  delete[] weights;
}

void Graph::genMinTree(Node *root)
{
  Queue<Node> *queue = new Queue<Node>();
  queue->enqueue(root);

  Node *current = root;
  HashTable<Edge> *edges = current->getForwardEdges();
  Item<Edge> *itemEdge = edges->getFirstItem();
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
      cout << "NULL";
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

  Heap<Node> *heap = new Heap<Node>(nEdges);

  Node *current;
  int n = sizeof(nodeLabels) / sizeof(int);
  for (int i = 1; i < n; ++i)
  {
    current = nodes->getItem(nodeLabels[i])->getData();
    current->setIn(0);
    current->setOut(INT_MAX);
  }
  current = nodes->getItem(nodeLabels[0])->getData();
  current->setIn(0);
  current->setOut(0);
  heap->insert(0, NULL, current);
  Node *root = current;

  HashTable<Edge> *edges;
  Item<Edge> *itemEdge;
  Edge *edge;
  Node *neighbor = NULL;
  int i = 0;
  while (true)
  {
    current = heap->remove(0);

    if (neighbor->getIn() == 0)
    {
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
        double weight = edge->getWeight();
        neighbor = edge->getNeighborPointer();
        if (neighbor->getOut() > weight)
        {
          neighbor->setOut(weight);
          neighbor->setPredecessor(current);

          heap->insert(weight, current, neighbor);
        }
        itemEdge = edges->getNextItem(itemEdge);
      }
    }
  }

  delete heap;

  genMinTree(root);
}

void Graph::kruskal(int *nodeLabels)
{
  if (isOriented)
  {
    return;
  }

  Heap<Node> *heap = new Heap<Node>(nEdges);

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
      double weight = edge->getWeight();
      neighbor = edge->getNeighborPointer();

      neighbor->setPredecessor(current);

      heap->insert(weight, current, neighbor);
    }
  }

  Node *root = NULL;

  int i = 0;
  while (i < n)
  {
    current = heap->remove(0);

    if (current->getIn() == 0)
    {
      current->setIn(1);
      if (++i == 1)
      {
        current->setPredecessor(NULL);
        root = current;
      }
    }
  }

  delete heap;

  if (root != NULL)
  {
    genMinTree(root);
  }
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
    if (current->getIn() == -1)
    {
      current->setIn(1);
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
      cout << nodeAbove->getLabel();
    }
    cout << " -> " << current;

    edges = current->getForwardEdges();
    itemEdge = edges->getFirstItem();
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

  Item<Node> *itemNode = nodes->getFirstItem();
  Node *current = itemNode->getData();
  while (current != NULL)
  {
    if (current->getIn() == -1)
    {
      stack->push(nodes->getFirstItem()->getData());

      HashTable<Edge> *edges = current->getForwardEdges();
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
    itemNode = nodes->getNextItem(itemNode);
  }

  delete stack;

  while (!sort->isEmpty())
  {
    cout << sort->pop()->getLabel() << " ";
  }

  delete sort;
}

int Graph::getNumDeClientes() {
  return order - 1;
}

double Graph::getCustomerDemand(int label) {
  return nodes->getItem(label)->getData()->getCustomerDemand();
}
