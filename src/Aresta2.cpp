#include <iostream>
#include <stdlib.h>
#include <string>
#include "Aresta2.h"

using namespace std;

Aresta::Aresta(No* no, Aresta* proxAresta) {
    pesoAresta = 1;
    this->noDestino = no;
    this->proxAresta = proxAresta;
}
Aresta::Aresta(No* no, Aresta* proxAresta, int peso) {
    pesoAresta = peso;
    this->noDestino = no;
    this->proxAresta = proxAresta;
}

int Aresta::getPesoAresta() {
    return pesoAresta;
}

void Aresta::setPesoAresta(int peso) {
    pesoAresta = peso;
}

No* Aresta::getNoDestino() {
    return noDestino;
}

void Aresta::setNoDestino(No* no) {
    this->noDestino = no;
}

Aresta* Aresta::getProxAresta() {
    return proxAresta;
}

void Aresta::setProxAresta(Aresta* aresta) {
    proxAresta = aresta;
}
