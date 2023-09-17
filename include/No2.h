#ifndef NO_H
#define NO_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include "Aresta2.h"

using namespace std;

class Aresta;

class No {
    private:
        int idNo;
        int pesoNo;
        int grauEntrada;
        int grauSaida;
        No* proxNo;
        Aresta* primeiraAresta;
        Aresta* ultimaAresta;

    public: 
        No(int idNo);
        No(int idNo, int peso);
        virtual ~No();
        int getIdNo();
        void setIdNo(int id);
        int getPesoNo();
        void setPesoNo(int peso);
        int getGrau();
        void incGrau();
        void decGrau();
        int getGrauEntrada();
        void incGrauEntrada();
        void decGrauEntrada();
        int getGrauSaida();
        void incGrauSaida();
        void decGrauSaida();
        No* getProxNo();
        void setProxNo(No* no);
        Aresta* getPrimeiraAresta();
        void setPrimeiraAresta(Aresta* aresta);
};