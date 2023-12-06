#ifndef HEAPELEMENT_H
#define HEAPELEMENT_H

template <typename T>
class HeapElement
{
private:
  int key;
  T *data;
  T *predecessor;

public:
  HeapElement(double key, T *predecessor, T *data);

  double getKey();
  T *getData();
  T *getPredecessor();
};

#include "../../src/DataStructures/heapElement.tpp"

#endif // HEAPELEMENT_H