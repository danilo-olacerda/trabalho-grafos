#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "Graph.h"
#include "Edge.h"
#include "HashTable.h"

using namespace std;

class Node
{
private:
    HashTable<Edge> *edges;
    unsigned int inDegree;
    unsigned int outDegree;
    float weight;
    bool visited;

public:
    Node(int id);
    ~Node();
};

#endif
