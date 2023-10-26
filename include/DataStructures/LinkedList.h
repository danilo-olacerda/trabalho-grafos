#ifndef LinkedList_H
#define LinkedList_H

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

  void addItem(int id, T data);
  void removeItem(int id, int *status);
};

#endif