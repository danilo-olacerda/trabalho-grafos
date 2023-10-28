#ifndef MINHEAP_H
#define MINHEAP_H

#include "Item.h"

template <typename T>
class MinHeap
{
private:
  Item<T> *first;
  int length;

public:
  Stack();
  ~Stack();

  bool isEmpty();

  void push(T *data);
  T *pop();
};

#endif // MINHEAP_H