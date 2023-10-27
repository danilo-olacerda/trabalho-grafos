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

  void addItem(int id, T *data);
  void removeItem(int id, int *status);

  Item<T> *getItem(int id);
  Item<T> *getFirstItem();
  Item<T> *getNextItem(Item<T> *item);
};

#endif // HASHTABLE_H