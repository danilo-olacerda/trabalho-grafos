#include <stdlib.h>
#include "../include/No.h"

No::No(int i, float x, float y)
{
  this->indice = i;
  this->coordX = x;
  this->coordY = y;
  this->demanda = 0;
}

No::No(int tam)
{
  int vet(n);
}

No::~No()
{

}
//gets

int No::getindice()
{
  return indice;
}

float No::getcoordX()
{
  return coordX;
}

float No::getcoordY()
{
  return coordY;
}

int No::getdemanda()
{
  return demanda;
}



//sets

void No::setcoordX(float x)
{
  coordX = x;
}
void No::setcoordY(float y)
{
  coordY = x;
}
void No::setdemanda(int d)
{
  demanda = d;
}

