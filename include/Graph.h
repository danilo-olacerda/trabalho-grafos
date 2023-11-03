#ifndef GRAPH_H
#define GRAPH_H

#include "DataStructures/HashTable.h"
#include "DataStructures/Stack.h"
#include "DataStructures/MinHeap.h"
#include "Node.h"

class Graph
{
private:
    HashTable<Node> *nodes;
    int order;
    int nEdges;
    bool isOriented;
    bool isSucessionAdj;
    void dfs(int label, bool isForward);
    void dfsWithStepAndPrecedencyRegister(int label);

public:
    Graph(bool isOriented);
    ~Graph();

    int getOrder();
    int getNEdges();

    void addNode(int label);
    void removeNode(int label);

    void addEdge(int tail, int head);
    void removeEdge(int tail, int head);

    void directTransitiveClosure(int label);
    void indirectTransitiveClosure(int label);

    void dijkstra(int label1, int label2);

    void generateNodeTree(int label);
};

#endif // GRAPH_H