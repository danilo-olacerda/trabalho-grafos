#ifndef EDGE_H
#define EDGE_H

#include "Node.h"

class Edge
{
private:
    Node *headPointer;
    float weight;

public:
    Edge(Node *headPointer);
};

#endif // EDGE_H