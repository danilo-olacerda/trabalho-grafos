#include "stdlib.h"
#include "../../include/DataStructures/HashTable.h"

template <typename T>
HashTable<T>::HashTable(int length)
{
  array = new LinkedList<T>()[length];
  this->length = length;
}

template <typename T>
HashTable<T>::~HashTable()
{
  for (int i = 0; i < length; i++)
  {
    delete array[i];
  }
  delete[] array;
}

template <typename T>
int HashTable<T>::hash(int id)
{
  return id % length;
}

template <typename T>
void HashTable<T>::addItem(int id, T *data)
{
  array[hash(id)]->addItemInList(id, data);
}

template <typename T>
void HashTable<T>::removeItem(int id, int *status)
{
  array[hash(id)]->removeItemFromList(id, status);
}

template <typename T>
Item<T> *HashTable<T>::getItem(int id)
{
  Item<T> item = array[hash(id)]->first;
  while (item != NULL)
  {
    if (item->id == id)
    {
      return item;
    }
    item = item->next;
  }
  return NULL;
}

template <typename T>
Item<T> *HashTable<T>::getFirstItem()
{
  Item<T> item = array[0]->getFirstInList();

  if (item == NULL)
  {
    int hash = 1;
    while (item != NULL && hash < length - 1)
    {
      item = array[++hash]->getFirstInList();
    }
  }

  return item;
}

template <typename T>
Item<T> *HashTable<T>::getNextItem(Item<T> *item)
{
  if (item != NULL)
  {
    int hash = hash(item->id);
    item = item->next;

    if (item == NULL && hash < length - 1)
    {
      while (item != NULL && hash < length - 1)
      {
        item = array[++hash]->getFirstInList();
      }
    }
  }

  return item;
}