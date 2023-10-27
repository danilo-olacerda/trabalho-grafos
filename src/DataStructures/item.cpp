#include "stdlib.h"
#include "../../include/DataStructures/Item.h"

template <typename T>
Item<T>::Item(int id, T *data)
{
  this->id = id;
  this->data = data;
  next = NULL;
}

template <typename T>
int Item<T>::getId()
{
  return id;
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
void Item<T>::setNext(Item<T> *next)
{
  this->next = next;
}