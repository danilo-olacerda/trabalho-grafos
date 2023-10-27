#include "stdlib.h"
#include "../../include/DataStructures/Item.h"

template <typename T>
Item<T>::Item(int id, T *data)
{
  this->id = id;
  this->data = data;
  next = NULL;
}