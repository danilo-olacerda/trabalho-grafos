#include "stdlib.h"
#include "Item.h"
#include "HashTable.h"

Item::Item(int id, void *data)
{
  this->id = id;
  this->data = data;
  next = NULL;
}