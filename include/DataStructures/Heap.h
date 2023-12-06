#ifndef MINHEAP_H
#define MINHEAP_H

#include "HeapElement.h"

template <typename T>
class Heap
{
private:
  HeapElement<T> **array;
  int length;
  int max;

public:
  Heap(int length);
  ~Heap();

  void insert(double key, T *nodePointer, T *data);
  T *remove(int i);
};

#include "../../src/DataStructures/heap.tpp"

#endif // MINHEAP_H