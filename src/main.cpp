#include "stdio.h"
#include "../include/Graph.h"

int main()
{
    int order = 6;

    Graph *graph = new Graph();

    for (int i = 0; i < order; i++)
    {
        graph->addNode(i);
    }
}