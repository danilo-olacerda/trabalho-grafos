#include <stdlib.h>

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
void LinkedList<T>::addItemInList(int key, T *data)
{
  Item<T> *item = new Item<T>(key, data);
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
void LinkedList<T>::removeItemFromList(int key, int *status)
{
  if (length == 0)
    return;

  if (first->getKey() == key)
  {
    Item<T> *temp = first->getNext();
    delete first;
    first = temp;
    --length;
    if (length == 0)
    {
      last = NULL;
    }
    *status = 0;
    return;
  }
  if (length == 1)
    return;

  Item<T> *item = first;
  while (item->getNext() != last)
  {
    item = item->getNext();
    if (item->getNext()->getKey() == key)
    {
      Item<T> *temp = item->getNext()->getNext();
      delete item->getNext();
      item->setNext(temp);
      --length;
      *status = 0;
      return;
    }
  }

  if (last->getKey() == key)
  {
    item->setNext(NULL);
    delete last;
    --length;
    *status = 0;
    return;
  }

  *status = 1;
}