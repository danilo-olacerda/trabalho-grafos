#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "Node.h"

class Graph
{
private:
    int order;
    int nEdges;
    Node *hash;
    int nHash;

public:
    Graph(int order);

    ~Graph();

    int getOrder();

    int getNEdges();

    void insertNode(int id);

    void insertEdge(int id, int targetId, float weight);

    void removeNode(int id);

    bool searchNode(int id);

    Node *getNode(int id);

    bool searchEdge(int id, int target_id);
};

#endif
