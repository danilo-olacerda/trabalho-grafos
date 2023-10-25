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
void HashTable<T>::addItem(int id, T data)
{
  array[hash(id)]->addItem(id, data);
}

template <typename T>
void HashTable<T>::addItem(int id, T data)
{
  array[hash(id)]->addItem(id, data);
}

template <typename T>
void HashTable<T>::removeItem(int id, u_int8_t *status)
{
  array[hash(id)]->removeItem(id, status);
}