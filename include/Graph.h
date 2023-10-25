#include "HashTable.h"
#include "Node.h"

class Graph
{
private:
    HashTable<Node> *nodes;
    int order;
    int nEdges;

public:
    Graph(int order);
    ~Graph();

    int getOrder();
    int getNEdges();

    void addNode(int id);
    void removeNode(int id);
};
