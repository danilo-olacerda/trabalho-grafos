#include "stdlib.h"
#include "Item.h"
#include "HashTable.h"

template <typename T>
Item<T>::Item(int id, T *data)
{
  this->id = id;
  this->data = data;
  next = NULL;
}