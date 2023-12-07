#ifndef QUEUE_H
#define QUEUE_H

#include "Item.h"

template <typename T>
class Queue
{
private:
  Item<T> *first;
  Item<T> *last;
  int length;

public:
  Queue();
  ~Queue();

  bool isEmpty();

  void enqueue(T *data);
  T *dequeue();
};

#include "../../src/DataStructures/queue.tpp"

#endif // QUEUE_H