#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "Edge.h" // Include of the Edge class

using namespace std;

class Node
{
private:
    int id;
    Node *next;

public:
    Node(int id);
    ~Node();
    int getId();
};

#endif
