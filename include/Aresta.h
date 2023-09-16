#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include "No.h"

using namespace std;

class No;

class Aresta {
public:
    Aresta(int noDestino, Aresta *proxAresta);
    ~Aresta();

    int getPesoAresta();
    Aresta *getProxAresta();
    void setProxAresta(Aresta *valor);
    void setNoDestino(int noDestino);
    int getNoDestino();

private:
    int pesoAresta;
    int idNoDestino;
    Aresta *proxAresta;
};

#endif // ARESTA_H
