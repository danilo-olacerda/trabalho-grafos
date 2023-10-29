#ifndef MINHEAP_H
#define MINHEAP_H

#include "HeapElement.h"

template <typename T>
class MinHeap
{
private:
  HeapElement<T> *array;
  int length;
  int offset;

public:
  MinHeap();
  ~MinHeap();

  void queue(T *data);
  T *unqueue();
};

#endif // MINHEAP_H