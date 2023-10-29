#ifndef NODE_H
#define NODE_H

#include "Edge.h"
#include "DataStructures/HashTable.h"

using namespace std;

class Node
{
private:
    int label;
    HashTable<Edge> *edges;
    float weight;
    unsigned int inDegree;
    unsigned int outDegree;
    int in; // Em DFS: demarca se o node já foi acessado, ou demarca o "tempo" em que o node foi acessado, quando for necessário
            // Em Dijkstra: demarca a menor distância de um nó específico até este nó

    int out; // Em DFS: demarca o "tempo" em que o DFS saiu do node, quando for necessário

    Item<Node> *predecessor;

public:
    Node(int label);
    Node(int label, float weight);
    ~Node();

    HashTable<Edge> *getEdges();

    int getLabel();
    int getIn();
    void setIn(int phase);
    int getOut();
    void setOut(int phase);
    Item<Node> *getPredecessor();
    void setPredecessor(Item<Node> *predecessor);

    void incrementInDegree();
    void decrementInDegree();

    void addEdge(int neighbor, Node *neighborPointer);
    void removeEdge(int neighbor, int *status);
};

#endif // NODE_H