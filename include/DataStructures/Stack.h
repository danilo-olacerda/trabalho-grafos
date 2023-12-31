#ifndef STACK_H
#define STACK_H

#include "Item.h"

template <typename T>
class Stack
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

#include "../../src/DataStructures/stack.tpp"

#endif // STACK_H