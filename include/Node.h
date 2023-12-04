#ifndef NODE_H
#define NODE_H

#include "DataStructures/HashTable.h"
#include "./Edge.h"

class Edge;

using namespace std;

class Node
{
private:
    int label;
    HashTable<Edge> *forwardEdges;
    HashTable<Edge> *backwardEdges;
    unsigned int inDegree;
    unsigned int outDegree;
    double in;  // Em DFS: demarca se o node já foi acessado, ou demarca o período em que o node foi acessado, quando for necessário
    double out; // Em DFS: demarca o período em que o DFS saiu do node, quando for necessário
             // Em Dijkstra: demarca a menor distância de um nó específico até este nó

    Node *predecessor;

public:
    Node(int label);
    ~Node();

    HashTable<Edge> *getForwardEdges();
    HashTable<Edge> *getBackwardEdges();

    int getLabel();
    double getIn();
    void setIn(double value);
    double getOut();
    void setOut(double value);
    Node *getPredecessor();
    void setPredecessor(Node *predecessor);

    void incrementInDegree();
    void decrementInDegree() { inDegree--; };

    void addEdge(int neighbor, Node *neighborPointer, bool isForward);
    void removeEdge(int neighbor, bool isForward, int *status);
};

#endif // NODE_H