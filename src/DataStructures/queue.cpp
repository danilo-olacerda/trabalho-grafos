#include <stdlib.h>
#include "../../include/DataStructures/MinHeap.h"

template <typename T>
Queue<T>::Queue(int length)
{
  array = new HeapElement<T>(length);
  length = 0;
  offset = 0;
}

template <typename T>
Queue<T>::~Queue()
{
  delete array;
}

template <typename T>
void Queue<T>::enqueue(int key, T *predecessor, T *data)
{
}