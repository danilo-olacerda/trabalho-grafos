#include "../../include/DataStructures/HeapElement.h"

template <typename T>
HeapElement<T>::HeapElement(double key, T *predecessor, T *data)
{
    this->key = key;
    this->data = data;
    this->predecessor = predecessor;
}

template <typename T>
double HeapElement<T>::getKey()
{
    return key;
}

template <typename T>
T* HeapElement<T>::getData()
{
    return data;
}