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
  while (!stack->isEmpty())
  {
    Node *node = stack->pop();
    if (node->getIn() == -1)
    {
      node->setIn(1);

      HashTable<Edge> *edges = isForward ? node->getForwardEdges() : node->getBackwardEdges();
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
  Stack<Node> *sort = new Stack<Node>();

  Node *current = nodes->getFirstItem()->getData();
  while (current != NULL)
  {
    if (current->getIn() == -1)
    {
      Stack<Node> *stack = new Stack<Node>();

      stack->push(nodes->getFirstItem()->getData());
      while (!stack->isEmpty())
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

    delete sort;
  }
}

void Graph::generateNodeTree(int label)
{
  Stack<Node> *stack = new Stack<Node>();

  int step = -1;
  stack->push(nodes->getItem(label)->getData());
  while (!stack->isEmpty())
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

void Graph::prim(int startVertex) {
    vector<bool> visited(order, false);
    vector<Edge> minSpanningTree;
    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> pq;

    pq.push({0, startVertex});

    while (!pq.empty()) {
        float weight = pq.top().first;
        int currentVertex = pq.top().second;
        pq.pop();

        if (visited[currentVertex]) {
            continue;
        }

        visited[currentVertex] = true;

        if (currentVertex != startVertex) {

            Node* currentNode = nodes[currentVertex];
            Node* predecessorNode = currentNode->getPredecessor();


            Item<Edge>* edgeItem = currentNode->getForwardEdges()->getItem(predecessorNode->getLabel());
            if (edgeItem) {
                Edge edge(predecessorNode, edgeItem->data.weight);
                minSpanningTree.push_back(edge);
            }
        }


        HashTable<Edge>* forwardEdges = currentNode->getForwardEdges();
        for (Item<Edge>* edgeItem = forwardEdges->getFirstItem(); edgeItem; edgeItem = forwardEdges->getNextItem(edgeItem)) {
            int to = edgeItem->label;
            Edge edge = edgeItem->data;
            if (!visited[to]) {
                pq.push({edge.weight, to});

                nodes[to]->setPredecessor(currentNode);
            }
        }
    }

    cout << "Minimum Spanning Tree:" << endl;
    for (const Edge& edge : minSpanningTree) {
        cout << startVertex << " - " << edge.neighborPointer->getLabel() << " (Weight: " << edge.weight << ")\n";
    }
}

void Graph::kruskal(int V) {
    vector<Edge> allEdges;
    vector<Edge> minSpanningTree;

    for (int i = 0; i < V; ++i) {
        HashTable<Edge>* forwardEdges = nodes[i]->getForwardEdges();
        for (Item<Edge>* edgeItem = forwardEdges->getFirstItem(); edgeItem; edgeItem = forwardEdges->getNextItem(edgeItem)) {
            Edge edge(i, edgeItem->label, edgeItem->data.weight);
            allEdges.push_back(edge);
        }
    }

    sort(allEdges.begin(), allEdges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    vector<int> parent(V, -1);

    for (const Edge& edge : allEdges) {
        int set1 = findParent(parent, edge.from);
        int set2 = findParent(parent, edge.to);

        if (set1 != set2) {
            minSpanningTree.push_back(edge);
            unionSets(parent, set1, set2);
        }
    }

    cout << "Minimum Spanning Tree:" << endl;
    for (const Edge& edge : minSpanningTree) {
        cout << edge.from << " - " << edge.to << " (Weight: " << edge.weight << ")\n";
    }
}

int Graph::findParent(vector<int>& parent, int vertex) {
    if (parent[vertex] == -1)
        return vertex;
    return findParent(parent, parent[vertex]);
}

void Graph::unionSets(vector<int>& parent, int set1, int set2) {
    parent[set1] = set2;
}
