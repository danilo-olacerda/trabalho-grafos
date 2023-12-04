#include <stdlib.h>
#include "../../include/DataStructures/Queue.h"

template <typename T>
Queue<T>::Queue()
{
  this.array = new HeapElement<T>(length);
  this.length = 0;
  this.offset = 0;
}

template <typename T>
Queue<T>::~Queue()
{
  delete array;
}

template <typename T>
void Queue<T>::enqueue(T *data)
{
}