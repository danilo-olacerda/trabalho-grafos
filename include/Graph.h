#ifndef GRAPH_H
#define GRAPH_H

#include "DataStructures/HashTable.h"
#include "Node.h"

class Graph
{
private:
    HashTable<Node> *nodes;
    int order;
    int nEdges;
    bool isOriented;
    bool isSucessionAdj;

public:
    Graph(bool isOriented, bool isSucessionAdj);
    ~Graph();

    int getOrder();
    int getNEdges();

    void addNode(int label);
    void removeNode(int label);

    void addEdge(int tail, int head);
    void removeEdge(int tail, int head);

    void transitiveClosure(int label);
};

#endif // GRAPH_H