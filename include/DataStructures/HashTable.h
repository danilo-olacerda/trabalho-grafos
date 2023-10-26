#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinkedList.h"

template <typename T>
class HashTable
{
private:
  LinkedList<T> *array;
  int length;

public:
  HashTable(int length);
  ~HashTable();

  int hash(int id);

  void addItem(int id, T data);
  void removeItem(int id, int *status);

  T *getData(int id);
};

#endif // HASHTABLE_H