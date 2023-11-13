#include <stdlib.h>
#include "../../include/DataStructures/MinHeap.h"

template <typename T>
MinHeap<T>::MinHeap(int length)
{
  array = new HeapElement<T>(length);
  length = 0;
  offset = 0;
}

template <typename T>
MinHeap<T>::~MinHeap()
{
  delete array;
}

template <typename T>
void MinHeap<T>::queue(int key, T *predecessor, T *data)
{

}