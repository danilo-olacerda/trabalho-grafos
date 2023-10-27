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
    int in;  // demarca quando o DFS chegou no node
    int out; // demarca quando o DFS saiu do node
    // Quando não for necessário essas duas informações, in será um marcador de visitado e out não será usado

public:
    Node();
    ~Node();

    HashTable<Edge> *getEdges();

    int getIn();
    void setIn(int phase);
    int getOut();
    void setOut(int phase);

    void incrementInDegree();
    void decrementInDegree();

    void addEdge(int neighbor, Node *neighborPointer);
    void removeEdge(int neighbor, int *status);
};

#endif // NODE_H