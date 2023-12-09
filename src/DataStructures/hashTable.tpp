#include "stdlib.h"

template <typename T>
HashTable<T>::HashTable(int length)
{
  array = new LinkedList<T> *[length];
  for (int i = 0; i < length; i++)
  {
    array[i] = new LinkedList<T>();
  }
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
int HashTable<T>::hash(int key)
{
  return key % length;
}

template <typename T>
void HashTable<T>::addItem(int key, T *data)
{
  array[hash(key)]->addItemInList(key, data);
}

template <typename T>
void HashTable<T>::removeItem(int key, int *status)
{
  array[hash(key)]->removeItemFromList(key, status);
}

template <typename T>
Item<T> *HashTable<T>::getItem(int key)
{
  Item<T> *item = array[hash(key)]->getFirstItemInList();
  while (item != NULL)
  {
    if (item->getKey() == key)
    {
      return item;
    }
    item = item->getNext();
  }

  return NULL;
}

template <typename T>
Item<T> *HashTable<T>::getFirstItem()
{
  Item<T> *item = array[0]->getFirstItemInList();

  if (item == NULL)
  {
    int hash = 1;
    while (item != NULL && hash < length - 1)
    {
      item = array[++hash]->getFirstItemInList();
    }
  }

  return item;
}

template <typename T>
Item<T> *HashTable<T>::getNextItem(Item<T> *item)
{
  if (item != NULL)
  {
    int hash = this->hash(item->getKey());
    item = item->getNext();

    if (item == NULL && hash < length - 1)
    {
      while (item != NULL && hash < length - 1)
      {
        item = array[++hash]->getFirstItemInList();
      }
    }
  }

  return item;
}