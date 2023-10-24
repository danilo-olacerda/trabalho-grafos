#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

using namespace std;

class Edge
{
private:
    int source;
    int target_id;
    Edge *next_edge;
    float weight;

public:
    Edge(int target_id);
    ~Edge();
    int getTargetId();
    int getSource();
    Edge *getNextEdge();
    float getWeight();
    void setNextEdge(Edge *edge);
    void setWeight(float weight);
    void setSource(int source);
};

#endif