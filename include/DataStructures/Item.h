#ifndef ITEM_H
#define ITEM_H

template <typename T>
class Item
{
private:
  int key;
  T *data;
  Item<T> *next;

public:
  Item(int key, T *data);

  int getKey();
  T *getData();
  Item<T> *getNext();
  void setNext(Item<T> *next);
};

#include "../../src/DataStructures/item.tpp"

#endif // ITEM_H