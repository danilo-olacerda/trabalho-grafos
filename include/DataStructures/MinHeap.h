#ifndef MINHEAP_H
#define MINHEAP_H

#include "HeapElement.h"

template <typename T>
class MinHeap
{
private:
  HeapElement<T> **array;
  int length;
  int offset;

public:
  MinHeap(int length);
  ~MinHeap();

  void enqueue(double key, T *nodePointer, T *data);
  T *dequeue();
};

#endif // MINHEAP_H