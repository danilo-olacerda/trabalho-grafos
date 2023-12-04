#ifndef EDGE_H
#define EDGE_H

#include "Node.h"

class Node;

class Edge
{
private:
    Node *neighborPointer;
    double weight;

public:
    Edge(Node *neighborPointer);
    Edge(Node *neighborPointer, double weight);

    Node *getNeighborPointer();
    double getWeight();
};

#endif // EDGE_H