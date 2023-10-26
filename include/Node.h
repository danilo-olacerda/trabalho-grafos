#ifndef NODE_H
#define NODE_H

#include "Edge.h"
#include "DataStructures/HashTable.h"

using namespace std;

class Node
{
private:
    HashTable<Edge> *edges;
    unsigned int inDegree;
    unsigned int outDegree;

public:
    Node();
    ~Node();

    void incrementInDegree();
    void decrementInDegree();

    void addEdge(int head, Node *headPointer);
    void removeEdge(int head, int *status);
};

#endif // NODE_H