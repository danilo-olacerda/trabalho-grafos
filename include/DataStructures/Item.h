#ifndef ITEM_H
#define ITEM_H

template <typename T>
class Item
{
private:
  int id;
  T *data;
  Item<T> *next;

public:
  Item(int id, T *data);

  int getId();
  T *getData();
  Item<T> *getNext();
};

#endif // ITEM_H