#ifndef GRAPMETRICS_H
#define GRAPMETRICS_H

#include "./Graph.h"

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
    double calcRadius();
    double calcDiameter();
    int *calcCenter();
    int *calcPeriphery();
    int *calcArticulationVertices();
};

#endif // GRAPMETRICS_H