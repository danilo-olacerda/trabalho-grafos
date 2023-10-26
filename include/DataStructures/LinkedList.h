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

  void addItemInList(int id, T data);
  void removeItemFromList(int id, int *status);
};

#endif // LINKEDLIST_H