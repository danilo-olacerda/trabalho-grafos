#include "LinkedList.h"

template <typename T>
class HashTable
{
private:
  LinkedList<T> *array;
  int length;

public:
  HashTable(int length);
  ~HashTable();

  int hash(int id);

  void addItem(int id, T data);
  void removeItem(int id, u_int8_t *status);
};