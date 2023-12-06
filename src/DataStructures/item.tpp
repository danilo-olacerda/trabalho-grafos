#include "stdlib.h"

template <typename T>
Item<T>::Item(int key, T *data)
{
  this->key = key;
  this->data = data;
  next = NULL;
}

template <typename T>
int Item<T>::getKey()
{
  return key;
}

template <typename T>
T *Item<T>::getData()
{
  return data;
}

template <typename T>
Item<T> *Item<T>::getNext()
{
  return next;
}

template <typename T>
void Item<T>::setNext(Item<T> *nextToSet)
{
  this->next = nextToSet;
}