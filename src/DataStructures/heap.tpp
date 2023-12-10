#include <stdlib.h>
#include "../../include/DataStructures/Heap.h"

template <typename T>
Heap<T>::Heap(int length)
{
  array = new HeapElement<T> *[length];
  length = max = 0;
}

template <typename T>
Heap<T>::~Heap()
{
  delete[] array;
}

template <typename T>
int Heap<T>::getFather(int i)
{
  return (i - (i % 2 == 0 ? -2 : -1)) / 2;
}

template <typename T>
void Heap<T>::insert(double key, T *predecessor, T *data)
{
  if (length >= max)
  {
    return;
  }

  array[length] = new HeapElement<T>(key, predecessor, data);
  int iSon = length;
  int iFather = getFather(length);
  while (iFather >= 0)
  {
    HeapElement<T> *father = array[iFather];
    HeapElement<T> *son = array[iSon];
    if (father->getKey() <= son->getKey())
    {
      break;
    }
    HeapElement<T> *temp = son;
    son = father;
    father = temp;
    iSon = iFather;
    iFather = getFather(iSon);
  }
  ++length;
}

template <typename T>
T *Heap<T>::remove(int i)
{
  if (length == 0)
  {
    return NULL;
  }

  T *target = array[i]->getData();

  int iSon1 = i * 2 + 1;
  int iSon2 = i * 2 + 2;
  int smallerSon;
  HeapElement<T> *son1;
  HeapElement<T> *son2;
  while (iSon1 <= length || iSon2 <= length)
  {
    son1 = array[iSon1];
    son2 = array[iSon2];
    smallerSon = son1->getKey() < son2->getKey() ? iSon1 : iSon2;
    array[i] = array[smallerSon];

    i = smallerSon;
    iSon1 = i * 2 + 1;
    iSon2 = i * 2 + 2;
  }

  return target;
}