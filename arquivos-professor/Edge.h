/**************************************************************************************************
 * Implementation of the TAD Edge
 **************************************************************************************************/

#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

using namespace std;

// Definition of the Edge class
class Edge
{
    // Attributes
private:
    int source;
    int target_id;
    Edge *next_edge;
    float weight;

public:
    // Constructor
    Edge(int target_id);
    // Destructor
    ~Edge();
    // Getters
    int getTargetId();
    int getSource();
    Edge *getNextEdge();
    float getWeight();
    // Setters
    void setNextEdge(Edge *edge);
    void setWeight(float weight);
    void setSource(int source);
};

#endif // EDGE_H_INCLUDED