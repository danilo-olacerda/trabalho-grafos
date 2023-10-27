#include <stdlib.h>
#include "../../include/DataStructures/LinkedList.h"

template <typename T>
LinkedList<T>::LinkedList()
{
  first = NULL;
  last = NULL;
  length = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
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
Item<T> *LinkedList<T>::getFirstItemInList()
{
  return first;
}

template <typename T>
void LinkedList<T>::addItemInList(int id, T *data)
{
  Item<T> *item = new Item(id, data);
  if (length == 0)
  {
    first = last = item;
  }
  else
  {
    last->setNext(item);
  }
  ++length;
}

template <typename T>
void LinkedList<T>::removeItemFromList(int id, int *status)
{
  if (n == 0)
    return;

  if (first->id == id)
  {
    Item<T> *temp = first->getNext();
    delete first;
    first = temp;
    --length;
    if (n == 0)
    {
      last = NULL;
    }
    *status = 0;
    return;
  }
  if (n == 1)
    return;

  Item<T> *item = first;
  while (item->getNext() != last)
  {
    item = item->getNext();
    if (item->getNext()->getId() == id)
    {
      Item<T> temp = item->getNext()->getNext();
      delete item->getNext();
      item->setNext(temp);
      --length;
      *status = 0;
      return;
    }
  }

  if (last->getId() == id)
  {
    item->setNext(NULL);
    delete last;
    --length;
    *status = 0;
    return;
  }

  *status = 1;
}