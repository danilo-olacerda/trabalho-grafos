#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Item.h"

template <typename T>
class LinkedList
{
private:
  Item<T> *first;
  Item<T> *last;
  int length;

public:
  LinkedList();
  ~LinkedList();

  Item<T> *getFirstItemInList();

  void addItemInList(int key, T *data);
  void removeItemFromList(int key, int *status);
};

#include "../../src/DataStructures/linkedList.tpp"

#endif // LINKEDLIST_H