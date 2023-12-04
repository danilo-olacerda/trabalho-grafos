#ifndef GRAPMETRICS_H
#define GRAPMETRICS_H

#include "../Graph.hpp"

template <typename T>
class GrapMetrics
{
private:
    GrapMetrics(Graph *graph);
    ~GrapMetrics();
    Graph *graph;
    bool *visited;
    int *discoveryTime;
    int *low;
    int *parent;
    bool *articulationPoints;
    int time;
    void DFS(int u);
public:
    int calcRadius();
    int calcDiameter();
    int calcCenter();
    int calcPeriphery();
    int calcArticulationVertices();
};

#endif // GRAPMETRICS_H