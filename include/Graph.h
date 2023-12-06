#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "DataStructures/HashTable.h"
#include "DataStructures/Stack.h"
#include "DataStructures/MinHeap.h"
#include "DataStructures/Queue.h"

class Graph
{
private:
    HashTable<Node> *nodes;
    int order;
    int nEdges;
    bool isOriented;
    bool isSucessionAdj;
    void dfsForTransitiveClosure(int label, bool isForward);
    void genMinTree(Node *root);

public:
    Graph(bool isOriented);
    ~Graph();

    HashTable<Node> *getNodes();
    int getOrder();
    int getNEdges();

    void addNode(int label);
    void removeNode(int label);

    void addEdge(int tail, int head);
    void removeEdge(int tail, int head);

    void directTransitiveClosure(int label);
    void indirectTransitiveClosure(int label);

    void dijkstra(int label1, int label2);
    void floyd(int label1, int label2);

    void prim(int *nodeLabels);
    void kruskal(int *nodeLabels);

    void generateTree(int label);

    void topologicalSort();
};

#endif // GRAPH_H
