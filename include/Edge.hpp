#ifndef EDGE_H
#define EDGE_H

#include "Node.hpp"

class Node;

class Edge
{
private:
    Node *neighborPointer;
    float weight;

public:
    Edge(Node *neighborPointer);
    Edge(Node *neighborPointer, float weight);

    Node *getNeighborPointer();
    float getWeight();
};

#endif // EDGE_H