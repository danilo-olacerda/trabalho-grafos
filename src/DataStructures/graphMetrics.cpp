#include "stdlib.h"
#include "../../include/graphMetrics.h"
#include "../../include/Graph.h"

template <typename T>
GrapMetrics<T>::GrapMetrics(Graph *graph)
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

template <typename T>
GrapMetrics<T>::~GrapMetrics()
{
    delete[] visited;
    delete[] discoveryTime;
    delete[] low;
    delete[] parent;
    delete[] articulationPoints;
}

template <typename T>
int GrapMetrics<T>::calcRadius()
{
    int min = 0;

    int size = this->graph->getOrder();

    for (int i = 0; i < size; i++)
    {
        int max = 0;
        for (int j = 0; j < size; j++)
        {
            int distance = this->graph->dijkstra(i, j);
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

template <typename T>
int GrapMetrics<T>::calcDiameter()
{
    int max = 0;

    int size = this->graph->getOrder();

    for (int i = 0; i < size; i++)
    {
        int max = 0;
        for (int j = 0; j < size; j++)
        {
            int distance = this->graph->dijkstra(i, j);
            if (distance > max)
            {
                max = distance;
            }
        }
    }

    return max;
}

template <typename T>
int GrapMetrics<T>::calcCenter()
{
    int size = this->graph->getOrder();
    int radius = this->calcRadius();
    int *eccentricities = new int[size];
    int centerCount = 0;

    for (int i = 0; i < size; i++)
    {
        eccentricities[i] = 0;
    }

    for (int i = 0; i < size; i++)
    {
        int maxDistance = 0;
        for (int j = 0; j < size; j++)
        {
            int distance = this->graph->dijkstra(i, j);
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

template <typename T>
int GrapMetrics<T>::calcPeriphery()
{
    int size = this->graph->getOrder();
    int diameter = this->calcDiameter();
    int *eccentricities = new int[size];
    int peripheryCount = 0;

    for (int i = 0; i < size; i++)
    {
        eccentricities[i] = 0;
    }

    for (int i = 0; i < size; i++)
    {
        int maxDistance = 0;
        for (int j = 0; j < size; j++)
        {
            int distance = this->graph->dijkstra(i, j);
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

template <typename T>
int GrapMetrics<T>::calcArticulationVertices()
{
    int articulationVertices = new int[graph->getOrder()];
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
            articulationVertices.push_back(i);
        }
    }

    return articulationVertices;
}

template <typename T>
void GrapMetrics<T>::DFS(int u)
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