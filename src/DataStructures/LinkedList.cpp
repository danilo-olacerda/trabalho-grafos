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
  if (first->id == id)
  {
    Item *temp = first->next;
    delete first;
    first = temp;
    --length;
    return;
  }

  Item *item = first->next;
  while (item->next != item->last)
  {
    if (item->next->id == id)
    {
      Item temp = item->next->next;
      delete item->next;
      item->next = temp;
      --length;
      return;
    }
    item = item->next;
  }

  if (last->id == id)
  {
    item->next = NULL;
    delete last;
    --length;
  }
}