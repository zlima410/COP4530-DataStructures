#include <iostream>
#include <utility>
#include <string>

// Definition of class TVector
template <typename T>
TVector<T>::TVector() : capacity{SPARECAPACITY}, size{ 0 }
{

}

template <typename T>
TVector<T>::TVector(T val, int num)
{

}

template <typename T>
TVector<T>::~TVector() // destructor
{
    delete array;   // deallocates memory used for array
}

template <typename T>
TVector<T>::TVector(const TVector<T> &v) // copy constructor
{
    array = new T{ *v.array };  // creates a new copy of the input array
}

template <typename T>
TVector<T>& TVector<T>::operator=(const TVector<T> &v) // copy assignment operator
{
    if (this != &v) //checks if the lhs and rhs point to different data
        *array = *v.array;  // if true set the lhs array equal to the rhs
    return *this;
}

template <typename T>
TVector<T>::TVector(TVector<T> &&v) : array{ v.array } // move constructor
{
    v.array = nullptr;  // set array to null pointer so the data won't be destroyed
}

template <typename T>
TVector<T>& TVector<T>::operator=(TVector<T> &&v) // move assignment operator
{
    swap(array, v.array);   // swaps the two pointees with each other 
    return *this;
}