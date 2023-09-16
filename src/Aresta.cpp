#include <iostream>
#include <stdlib.h>
#include <string>
#include "Aresta.h"

using namespace std;

/**
 * Construtor. Os valores padrões são:\n
 *
 * peso = 1;
 *
 * @param *noDestino (new valor)
 * @param *proxAresta (new valor)
 */
Aresta::Aresta(int idDestino, Aresta *proxAresta) {
    this->idNoDestino = idDestino;
    this->proxAresta = proxAresta;
}
/** Destructor */
Aresta::~Aresta() {
    //dtor
}

/**
 * A funcao define peso valor.
 *
 * @param valor (new valor)
 */

/**
 * A funcao retorna peso valor.
 */
/**
 * A funcao define noDestino.
 *
 * @param valor (new valor)
 */
void Aresta::setNoDestino(int idDestino) {
    this->idNoDestino = idDestino;
}

/**
 * A funcao retorna noDestino.
 */
int Aresta::getNoDestino() {
    return this->idNoDestino;
}

/**
 * A funcao define proxAresta.
 *
 * @param valor (new valor)
 */
void Aresta::setProxAresta(Aresta *valor) {
    this->proxAresta = valor;
}

/**
 * A funcao retorna proxAresta;
 */
Aresta* Aresta::getProxAresta() {
    return this->proxAresta;
}
