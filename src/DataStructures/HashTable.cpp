#include "stdlib.h"
#include "HashTable.h"

template <typename T>
HashTable<T>::HashTable(int length)
{
  array = new T[length];
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