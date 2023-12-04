#ifndef QUEUE_H
#define QUEUE_H

#include "HeapElement.h"

template <typename T>
class Queue
{
private:
  HeapElement<T> **array;
  int length;
  int offset;

public:
  Queue();
  ~Queue();

  void enqueue(T *data);
  T *dequeue();
  bool isEmpty() { return length == 0; };
};

#endif // QUEUE_H