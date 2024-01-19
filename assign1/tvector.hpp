#include <iostream>
#include <utility>
#include <string>

// Definition of class TVector ==================================//
template <typename T>
TVector<T>::TVector() : capacity(SPARECAPACITY), size(0)
{
    array = new T[capacity]; // creates a new array with capacity = SPARECAPACITY
}

template <typename T>
TVector<T>::TVector(T val, int num) : capacity(SPARECAPACITY + num), size(num)
{

    array = new T[capacity];           // creates a new array with size = num
    for (int i = 0; i < num; i++) // sets each element of the array to val
        array[i] = val;
}

template <typename T>
TVector<T>::~TVector() // destructor
{
    delete[] array; // deallocates memory used for array
}

template <typename T>
TVector<T>::TVector(const TVector<T> &v) // copy constructor
{
    array = new T{*v.array}; // creates a new copy of the input array
}

template <typename T>
TVector<T> &TVector<T>::operator=(const TVector<T> &v) // copy assignment operator
{
    if (this != &v)        // checks if the lhs and rhs point to different data
        *array = *v.array; // if true set the lhs array equal to the rhs
    return *this;
}

template <typename T>
TVector<T>::TVector(TVector<T> &&v) : array{v.array} // move constructor
{
    v.array = nullptr; // set array to null pointer so the data won't be destroyed
}

template <typename T>
TVector<T> &TVector<T>::operator=(TVector<T> &&v) // move assignment operator
{
    std::swap(array, v.array); // swaps the two pointees with each other
    return *this;
}

template <typename T>
bool TVector<T>::IsEmpty() const // checks to see whether container is empty
{
    if (size == 0) // if size is 0 then the container is empty
        return true;
    else
        return false;
}

template <typename T>
void TVector<T>::Clear() // clear out Vector, reset to empty
{
    for (int i = 0; i < size; i++)
        array[i].~T();

    size = 0;
}

template <typename T>
int TVector<T>::GetSize() const { return size; }

template <typename T>
void TVector<T>::InsertBack(const T &d) // insert data d as last element
{
    if (size == capacity)
    {
        T *temp = new T[2 * capacity];

        for (int i = 0; i < capacity; i++)
        {
            temp[i] = std::move(array[i]);
        }

        delete[] array;
        capacity *= 2;
        array = temp;
    }

    array[size] = d;
    size++;
}

template <typename T>
void TVector<T>::RemoveBack() // remove last element of Vector
{
    if (size > 0) {
        size--;
        array[size].~T(); // sets the last element of the array to the default value of the type
    }
}

template <typename T>
T &TVector<T>::GetFirst() const
{
    return array[0]; // returns the first element of the array
}

template <typename T>
T &TVector<T>::GetLast() const
{
    return array[size - 1]; // returns the last elemnet of the array
}

template <typename T>
TVectorIterator<T> TVector<T>::GetIterator() const
{
}

template <typename T>
TVectorIterator<T> TVector<T>::GetIteratorEnd() const
{
}

template <typename T>
void TVector<T>::SetCapacity(unsigned int c)
{
    //reset the capacity of the vector to c and adjust size if c is smaller
    if (c < capacity)
    {
        capacity = c;
        size = c;
    }
    else
        capacity = c;

    T *temp = new T[capacity];

    for (int i = 0; i < size; i++)
    {
        temp[i] = std::move(array[i]);
    }

    delete[] array;
    array = temp;
}

template <typename T>
TVectorIterator<T> TVector<T>::Insert(TVectorIterator<T> pos, const T &d)
{
}

template <typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos)
{
}

template <typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos1, TVectorIterator<T> pos2)
{
}

template <typename T>
void TVector<T>::Print(std::ostream &os, char delim) const
{
    for (int i = 0; i < size; i++)
    {
        os << array[i] << delim;
    }
}