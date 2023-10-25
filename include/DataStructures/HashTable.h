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

  int getHash(int id);

  void addItem(int id, T data);
  void removeItem(int id);
};