#include <stdlib.h>
#include "LinkedList.h"

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
  Item *item = first;
  while (item != NULL)
  {
    Item *temp = item->next;
    delete item;
    item = temp;
  }
}

template <typename T>
void LinkedList<T>::addItem(int id, T data)
{
  Item *item = new Item(id, data);
  if (length == 0)
  {
    first = last = item;
  }
  else
  {
    last->next = item;
  }
  ++length;
}

template <typename T>
void LinkedList<T>::removeItem(int id)
{
  Item *item = first;

  if (item->id == id)
  {
    Item *temp = item;
    delete item;
    first = temp;
    --length;
    return;
  }

  while (item->next != item->last)
  {
    item = item->next;

    if (item->next->id == id)
    {
      Item temp = item->next->next;
      delete item->next;
      item->next = temp;
      --length;
      return;
    }
  }

  if (last->id == id)
  {
    item->next = NULL;
    delete last;
    --length;
  }
}