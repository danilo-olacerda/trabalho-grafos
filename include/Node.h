#include "Edge.h"
#include "HashTable.h"

using namespace std;

class Node
{
private:
    int label;
    HashTable<Edge> *edges;
    unsigned int inDegree;
    unsigned int outDegree;

public:
    Node(int label);
    ~Node();

    void addEdge(int head);
    void removeEdge(int head);
};
