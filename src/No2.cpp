#include "No2.h"

using namespace std;

No::No(int id) {
    idNo = id;
    pesoNo = 0;
    grauEntrada = 0;
    grauSaida = 0;
    proxNo = NULL;
    primeiraAresta = NULL;
}

No::No(int id, int peso) {
    idNo = id;
    pesoNo = peso;
    grauEntrada = 0;
    grauSaida = 0;
    proxNo = NULL;
    primeiraAresta = NULL;
}

No::~No() {
    for(Aresta* auxAresta = getPrimeiraAresta(); auxAresta != NULL; auxAresta = auxAresta->getProxAresta())
    while (auxAresta != NULL ) {
        Aresta* auxProxAresta = auxAresta->getProxAresta();
        delete(auxAresta);
        auxAresta = auxProxAresta;       
    }
}


int No::getIdNo() {
    return idNo;
}

void No::setIdNo(int id) {
    idNo = id;
}


int No::getPesoNo() {
    return pesoNo;
}

void No::setPesoNo(int valor) {
    pesoNo = valor;
}


int No::getGrau() {
    return grauSaida;
}
void No::incGrau() {
    grauEntrada++;
    grauSaida++;
}
void No::decGrau() {
    grauEntrada--;
    grauSaida--;
}


int No::getGrauEntrada() {
    return grauEntrada;
}
void No::incGrauEntrada() {
    grauEntrada++;
}
void No::decGrauEntrada() {
    this->grauEntrada--;
}


int No::getGrauSaida() {
    return grauSaida;
}
void No::incGrauSaida() {
    grauSaida++;
}
void No::decGrauSaida() {
    grauSaida--;
}


No* No::getProxNo(){
    return proxNo;
}

void No::setProxNo(No* no) {
    proxNo = no;
}


Aresta* No::getPrimeiraAresta(){
    return primeiraAresta;
}

void No::setPrimeiraAresta(Aresta* aresta) {
    primeiraAresta = aresta;
}
