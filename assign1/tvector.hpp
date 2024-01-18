#include <iostream>
#include <utility>
#include <string>

// Definition of class TVector
template <typename T>
TVector<T>::TVector()
{

}

template <typename T>
TVector<T>::TVector(T val, int num)
{

}

template <typename T>
TVector<T>::~TVector() // destructor
{
    delete array;
}

template <typename T>
TVector<T>::TVector(const TVector<T> &v) // copy constructor
{
    array = new T{ *v.array };
}

template <typename T>
TVector<T>& TVector<T>::operator=(const TVector<T> &v) // copy assignment operator
{
    if (this != &v)
        *array = *v.array;
    return *this;
}

template <typename T>
TVector<T>::TVector(TVector<T> &&v) : array{ v.array } // move constructor
{
    v.array = nullptr;
}

template <typename T>
TVector<T>& TVector<T>::operator=(TVector<T> &&v) // move assignment operator
{
    swap(array, v.array);
    return *this;
}