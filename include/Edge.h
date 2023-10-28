#ifndef EDGE_H
#define EDGE_H

#include "Node.h"

class Edge
{
private:
    Node *neighborPointer;
    float weight;

public:
    Edge(Node *neighborPointer);

    Node *getNeighborPointer();
    float getWeight();
};

#endif // EDGE_H