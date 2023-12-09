#include "stdlib.h"
#include <algorithm>
#include <vector>
#include "../../include/graphMetrics.h"
#include "../../include/Graph.h"
#include "../../include/Edge.h"

GrapMetrics::GrapMetrics(Graph *graph)
{
    this->graph = graph;
    int order = graph->getOrder();
    visited = new bool[order];
    discoveryTime = new int[order];
    low = new int[order];
    parent = new int[order];
    articulationPoints = new bool[order];
    time = 0;
}

GrapMetrics::~GrapMetrics()
{
    delete[] visited;
    delete[] discoveryTime;
    delete[] low;
    delete[] parent;
    delete[] articulationPoints;
}

double GrapMetrics::calcRadius()
{
    double min = 0;

    int size = this->graph->getOrder();

    for (int i = 0; i < size; i++)
    {
        double max = 0;
        for (int j = 0; j < size; j++)
        {
            double distance = this->graph->dijkstra(i, j);
            if (distance > max)
            {
                max = distance;
            }
        }
        if (max < min)
        {
            min = max;
        }
    }

    return min;
}

double GrapMetrics::calcDiameter()
{
    double max = 0;

    int size = this->graph->getOrder();

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            double distance = this->graph->dijkstra(i, j);
            if (distance > max)
            {
                max = distance;
            }
        }
    }

    return max;
}

int *GrapMetrics::calcCenter()
{
    int size = this->graph->getOrder();
    double radius = this->calcRadius();
    double *eccentricities = new double[size];
    int centerCount = 0;

    for (int i = 0; i < size; i++)
    {
        eccentricities[i] = 0;
    }

    for (int i = 0; i < size; i++)
    {
        double maxDistance = 0;
        for (int j = 0; j < size; j++)
        {
            double distance = this->graph->dijkstra(i, j);
            if (distance > maxDistance)
            {
                maxDistance = distance;
            }
        }
        eccentricities[i] = maxDistance;
        if (maxDistance < radius)
        {
            radius = maxDistance;
            centerCount = 1;
        }
        else if (maxDistance == radius)
        {
            centerCount++;
        }
    }

    int *centerVertices = new int[centerCount];
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        if (eccentricities[i] == radius)
        {
            centerVertices[index++] = i;
        }
    }

    delete[] eccentricities;
    return centerVertices;
}

int *GrapMetrics::calcPeriphery()
{
    int size = this->graph->getOrder();
    double diameter = this->calcDiameter();
    double *eccentricities = new double[size];
    int peripheryCount = 0;

    for (int i = 0; i < size; i++)
    {
        eccentricities[i] = 0;
    }

    for (int i = 0; i < size; i++)
    {
        double maxDistance = 0;
        for (int j = 0; j < size; j++)
        {
            double distance = this->graph->dijkstra(i, j);
            if (distance > maxDistance)
            {
                maxDistance = distance;
            }
        }
        eccentricities[i] = maxDistance;
        if (maxDistance > diameter)
        {
            diameter = maxDistance;
            peripheryCount = 1;
        }
        else if (maxDistance == diameter)
        {
            peripheryCount++;
        }
    }

    int *peripheryVertices = new int[peripheryCount];
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        if (eccentricities[i] == diameter)
        {
            peripheryVertices[index++] = i;
        }
    }

    delete[] eccentricities;
    return peripheryVertices;
}

int *GrapMetrics::calcArticulationVertices()
{
    vector<int>* articulationVertices = new vector<int>;
    int size = graph->getOrder();

    for (int i = 0; i < size; i++)
    {
        visited[i] = false;
        articulationPoints[i] = false;
        parent[i] = -1;
    }

    for (int i = 0; i < size; i++)
    {
        if (!visited[i])
        {
            DFS(i);
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (articulationPoints[i])
        {
            articulationVertices->push_back(i);
        }
    }

    int* array = new int[articulationVertices->size()];

    for (int i = 0; i < articulationVertices->size(); i++) {
        array[i] = articulationVertices->at(i);
    }

    return array;
}

void GrapMetrics::DFS(int u)
{
    visited[u] = true;
    discoveryTime[u] = low[u] = ++time;
    int children = 0;

    HashTable<Edge> *edges = graph->getNode(u)->getForwardEdges();
    Item<Edge> *currentEdge = edges->getFirstItem();

    while (currentEdge != NULL)
    {
        int v = currentEdge->getData()->getNeighborPointer()->getLabel();

        if (!visited[v])
        {
            children++;
            parent[v] = u;
            DFS(v);

            low[u] = min(low[u], low[v]);
            if (parent[u] == -1 && children > 1)
                articulationPoints[u] = true;
            if (parent[u] != -1 && low[v] >= discoveryTime[u])
                articulationPoints[u] = true;
        }
        else if (v != parent[u])
        {
            low[u] = min(low[u], discoveryTime[v]);
        }

        currentEdge = edges->getNextItem(currentEdge);
    }
}