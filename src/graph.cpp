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
  Stack<Node> stack = new Stack<Node>();

  stack.push(nodes->getItem(label)->getData());

  HashTable<Edge> *edges = isForward ? node->getForwardEdges() : node->getBackwardEdges();
  Item<Edge> *itemEdge = edges->getFirstItem();
  Node *neighbor;
  while (!stack.isEmpty())
  {
    Node *node = stack.pop();
    if (node->getIn() == -1)
    {
      node->setIn(1);

      while (itemEdge != NULL)
      {
        neighbor = itemEdge->getData()->getNeighborPointer();
        if (neighbor->getIn() == -1)
        {
          stack.push(neighbor);
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
  MinHeap<Node> minHeap = new MinHeap<Node>(nEdges);

  Item<Node> *itemNode = nodes->getFirstItem();
  while (itemNode != NULL)
  {
    itemNode->getData()->setOut(INT_MAX);
    itemNode = nodes->getNextItem(itemNode);
  }

  Node *current = nodes->getItem(label1)->getData();
  current->setOut(0);
  minHeap.enqueue(0, NULL, current);

  Node *destiny = nodes->getItem(label2)->getData();
  HashTable<Edge> *edges = current->getForwardEdges();
  Item<Edge> *itemEdge = edges->getFirstItem();
  Edge *edge;
  Node *neighbor;
  while (destiny->getPredecessor() == NULL)
  {
    current = minHeap.dequeue();
    if (current->getIn() == -1)
    {
      current->setIn(1);

      while (itemEdge != NULL)
      {
        edge = itemEdge->getData();
        neighbor = edge->getNeighborPointer();
        if (neighbor->getIn() == -1)
        {
          float weight = edge->getWeight();
          float dist = current->getIn() + weight;
          neighbor->setOut(dist);

          minHeap.enqueue(dist, current, neighbor);
        }

        itemEdge = edges->getNextItem(itemEdge);
      }
    }
  }

  delete minHeap;

  Stack<Node> stack = new Stack<Node>();

  Node *node = destiny;
  while (node != NULL)
  {
    stack.push(node);
    node = node->getPredecessor();
  }

  while (!stack.isEmpty())
  {
    std::cout << stack.pop()->getLabel() << " ";
  }

  delete stack;
}

void Graph::topologicalSort()
{
  Stack<Node> sort = new Stack<Node>();

  Node *current = nodes->getFirstItem()->getData();
  while (current != NULL)
  {
    if (current->getIn() == -1)
    {
      Stack<Node> stack = new Stack<Node>();

      stack->push(nodes->getFirstItem()->getData());

      HashTable<Edge> *edges = node->getForwardEdges();
      Item<Edge> *itemEdge = edges->getFirstItem();
      Node *neighbor;
      while (!stack.isEmpty())
      {
        Node *node = stack.pop();
        if (node->getIn() == -1)
        {
          node->setIn(1);
          stack.push(node);

          while (itemEdge != NULL)
          {
            neighbor = itemEdge->getData()->getNeighborPointer();
            if (neighbor->getIn() == -1)
            {
              stack.push(neighbor);
            }

            itemEdge = edges->getNextItem(itemEdge);
          }
        }
        else if (node->getOut() == -1)
        {
          sort.push(node);
        }
      }

      delete stack;
    }

    while (!sort.isEmpty())
    {
      cout << sort.pop()->getLabel() << " ";
    }

    delete sort;
  }
}

void Graph::generateNodeTree(int label)
{
  Stack<Node> stack = new Stack<Node>();

  int step = -1;
  stack.push(nodes->getItem(label)->getData());

  HashTable<Edge> *edges = node->getForwardEdges();
  Item<Edge> *itemEdge = edges->getFirstItem();
  Node *neighbor;
  while (!stack.isEmpty())
  {
    Node *node = stack.pop();
    if (node->getIn() == -1)
    {
      node->setIn(++step);
      stack.push(node);

      while (itemEdge != NULL)
      {
        neighbor = itemEdge->getData()->getNeighborPointer();
        if (neighbor->getIn() == -1)
        {
          neighbor->setPredecessor(node);
          stack.push(neighbor);
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

void Graph::genMinTree(Queue *queue)
{
  Node *current;
  Node *neighbor;
  HashTable<Edge> *edges = current->getForwardEdges();
  Item<Edge> *itemEdge = edges->getFirstItem();
  Edge *edge;
  while (!queue->isEmpty())
  {
    current = queue->dequeue();

    if (current->getPredecessor() != NULL)
    {
      cout << current->getPredecessor()->getLabel();
    }
    else
    {
      cout << "NULL"
    }
    cout << " -> " << current->getLabel() << "\n";

    while (itemEdge != NULL)
    {
      edge = itemEdge->getData();
      neighbor = edge->getNeighborPointer();
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
  minHeap.enqueue(0, NULL, current);

  Queue<Node> queue = new Queue<Node>();

  queue.enqueue(current);

  MinHeap<Node> minHeap = new MinHeap<Node>(nEdges);

  HashTable<Edge> *edges;
  Item<Edge> *itemEdge;
  Edge *edge;
  Node *neighbor;
  int i = 0;
  while (true)
  {
    current = minHeap.dequeue();

    if (current->getIn() == 0)
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
        float weight = edge->getWeight();
        neighbor = edge->getNeighborPointer();
        if (neighbor->getIn() == 0 && neighbor->getOut() > weight)
        {
          neighbor->setOut(weight);
          neighbor->setPredecessor(current);
          minHeap.enqueue(weight, current, neighbor);
        }
        itemEdge = edges->getNextItem(itemEdge);
      }
    }
  }

  delete minHeap;

  genMinTree(&queue);

  delete queue;
}

void Graph::kruskal(int *nodeLabels)
{
  MinHeap<Node> minHeap = new MinHeap<Node>(nEdges);

  HashTable<Edge> *edges;
  Item<Edge> *itemEdge;
  Edge *edge;
  Node *neighbor;

  Node *current;
  int n = sizeof(nodeLabels) / sizeof(int);
  for (int i = 1; i < n; ++i)
  {
    current = nodes->getItem(nodeLabels[i])->getData();
    current->setIn(0);
    edges = current->getForwardEdges();
    for (itemEdge = edges->getFirstItem(); itemEdge != NULL; itemEdge = edges->getNextItem(itemEdge))
    {
      edge = itemEdge->getData();
      float weight = itemEdge->getData;
      neighbor = edge->getNeighborPointer();

      neighbor->setPredecessor(current);

      minHeap.enqueue(weight, current, neighbor);
    }
  }

  Queue<Node> queue = new Queue<Node>();

  int i = 0;
  while (i < n)
  {
    current = minHeap.dequeue();

    if (current->getIn() == 0)
    {
      current->setIn(1);
      if (++i == 1)
      {
        current->setPredecessor(NULL);
        queue.enqueue(current);
      }
    }
  }

  delete minHeap;

  genMinTree(&queue);

  delete queue;
}