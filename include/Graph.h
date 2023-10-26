#ifndef Graph_H
#define Graph_H

#include "DataStructures/HashTable.h"
#include "Node.h"

class Graph
{
private:
    HashTable<Node> *nodes;
    int order;
    int nEdges;

public:
    Graph();
    ~Graph();

    int getOrder();
    int getNEdges();

    void addNode(int id);
    void removeNode(int id);
};

#endif