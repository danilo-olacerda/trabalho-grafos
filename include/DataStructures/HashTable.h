#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinkedList.h"
#include "Item.h"

template <typename T>
class HashTable
{
private:
  LinkedList<T> *array;
  int length;

public:
  HashTable(int length);
  ~HashTable();

  int hash(int key);

  void addItem(int key, T *data);
  void removeItem(int key, int *status);

  Item<T> *getItem(int key);
  Item<T> *getFirstItem();
  Item<T> *getNextItem(Item<T> *item);
};

#include "../../src/DataStructures/hashTable.tpp"

#endif // HASHTABLE_H