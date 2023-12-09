#include "stdlib.h"

template <typename T>
Queue<T>::Queue()
{
  first = NULL;
  last = NULL;
  length = 0;
}

template <typename T>
Queue<T>::~Queue()
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
bool Queue<T>::isEmpty()
{
  return length == 0;
}

template <typename T>
void Queue<T>::enqueue(T *data)
{
  Item<T> *item = new Item(0, data);
  item->setNext(NULL);
  last->setNext(item);
  last = item;

  ++length;
}

template <typename T>
T *Queue<T>::dequeue()
{
  T *data = first->getData();
  Item<T> *temp = first->getNext();
  delete first;
  first = temp;

  --length;

  return data;
}