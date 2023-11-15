#ifndef GRAPH_H
#define GRAPH_H

#include "DataStructures/HashTable.h"
#include "DataStructures/Stack.h"
#include "DataStructures/MinHeap.h"
#include "Node.hpp"

class Graph
{
private:
    HashTable<Node> *nodes;
    int order;
    int nEdges;
    bool isOriented;
    bool isSucessionAdj;
    void dfsForTransitiveClosure(int label, bool isForward);

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

    void topologicalSort();

    void generateNodeTree(int label);
    void prim(int startVertex);
    void kruskal(int V);
    int findParent(vector<int>& parent, int vertex);
    void unionSets(vector<int>& parent, int set1, int set2);
};

#endif // GRAPH_H
