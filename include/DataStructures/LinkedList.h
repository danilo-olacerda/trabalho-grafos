#include "Item.h"

template <typename T>
class LinkedList
{
private:
  Item *first;
  Item *last;
  int length;

public:
  LinkedList();
  ~LinkedList();

  void addItem(int id, T data);
  void removeItem(int id);
};