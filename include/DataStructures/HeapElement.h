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
  HeapElement(int key, T *data, T *predecessor);

  int getKey();
  T *getData();
  T *getPredecessor();
};

#endif // HEAPELEMENT_H