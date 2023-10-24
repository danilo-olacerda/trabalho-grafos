#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "Graph.h"
#include "Edge.h"

using namespace std;

class Node
{
private:
    int id;
    int idHash;
    Node *next;
    Node *adjList;
    int nAdjHash;
    Edge *nodeList;
    unsigned int in_degree;
    unsigned int out_degree;

public:
    Node(int id);
    ~Node();
    int getId();
};

#endif
