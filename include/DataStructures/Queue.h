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
  Queue(int length);
  ~Queue();

  void enqueue(T *data);
  T *dequeue();
};

#endif // QUEUE_H