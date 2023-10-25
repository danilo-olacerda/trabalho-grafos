#include "stdlib.h"
#include "HashTable.h"

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
int HashTable<T>::getHash(int id)
{
  return id % length;
}

template <typename T>
void HashTable<T>::addItem(int id, T data)
{
  array[getHash(id)]->addItem(id, data);
}

template <typename T>
void HashTable<T>::addItem(int id, T data)
{
  array[getHash(id)]->addItem(id, data);
}

template <typename T>
void HashTable<T>::removeItem(int id)
{
  array[getHash(id)]->removeItem(id);
}