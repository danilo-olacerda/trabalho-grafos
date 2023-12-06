#include <stdlib.h>
#include "../../include/DataStructures/Heap.h"

template <typename T>
Heap<T>::Heap(int length)
{
  array = new HeapElement<T>*[length];
  length = max = 0;
}

template <typename T>
Heap<T>::~Heap()
{
  delete [] array;
}

int getFather(int i)
{
  return (i - (i % 2 == 0 ? -2 : -1))/2;
}

template <typename T>
void Heap<T>::insert(double key, T *predecessor, T *data)
{
  if(length >= max)
  {
    return;
  }

  array[length] = new HeapElement(key, predecessor, data);
  int iSon = length;
  int iFather = getFather(length);
  while(iFather >= 0)
  {
    if(array[iFather]->getKey() <= array[iSon]->getKey())
    {
      break;
    }
    HeapElement<T> *temp = array[iSon];
    array[iSon] = array[iFather];
    array[iFather] = temp;
    iSon = iFather;
    int iFather = getFather(iSon);
  }
  ++length;
}

template <typename T>
T *Heap<T>::remove(int i)
{
  if(length == 0) 
  {
    return NULL;
  }
  
  T *target = array[i]->getData();

  int iSon1 = i * 2 + 1;
  int iSon2 = i * 2 + 2;
  int smallerSon;
  while(iSon1 <= length && iSon2 <= length) 
  {
    smallerSon = array[iSon1]->getKey() < array[iSon2]->getKey() ? iSon1 : iSon2;
    array[i] = array[smallerSon];
  }

  return target;
}