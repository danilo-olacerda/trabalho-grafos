#ifndef Item_H
#define Item_H

template <typename T>
class Item
{
private:
  int id;
  T *data;
  Item<T> *next;

public:
  Item(int id, T *data);
};

#endif