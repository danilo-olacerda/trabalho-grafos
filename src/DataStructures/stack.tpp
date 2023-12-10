#include "stdlib.h"

template <typename T>
Stack<T>::Stack()
{
  first = NULL;
  length = 0;
}

template <typename T>
Stack<T>::~Stack()
{
  Item<T> *item = first;
  while (item != NULL)
  {
    Item<T> *temp = item->getNext();
    delete item;
    item = temp;
  }
}

template <typename T>
bool Stack<T>::isEmpty()
{
  return length == 0;
}

template <typename T>
void Stack<T>::push(T *data)
{
  Item<T> *item = new Item<T>(0, data);
  item->setNext(first);
  first = item;

  ++length;
}

template <typename T>
T *Stack<T>::pop()
{
  T *data = first->getData();
  Item<T> *temp = first->getNext();
  delete first;
  first = temp;

  --length;

  return data;
}