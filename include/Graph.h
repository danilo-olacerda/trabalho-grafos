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

    int getNNodeHash();

    void insertNode(int id);

    void insertEdge(int id, int targetId, float weight);

    void removeNode(int id);

    bool searchNode(int id);

    Node *getNode(int id);

    bool searchEdge(int id, int target_id);
};
