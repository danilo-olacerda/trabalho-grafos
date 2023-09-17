#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include "No2.h"

using namespace std;

class No;

class Aresta {
private:
    int pesoAresta;
    No* noDestino;
    Aresta* proxAresta;

public:
    Aresta(No* no, Aresta* proxAresta);
    Aresta(No* no, Aresta* proxAresta, int peso);
    int getPesoAresta();
    void setPesoAresta(int peso);
    No* getNoDestino();
    void setNoDestino(No* no);
    Aresta* getProxAresta();
    void setProxAresta(Aresta* aresta);
};

#endif // ARESTA_H
