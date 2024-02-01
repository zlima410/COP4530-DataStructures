#include <iostream>
#include <string>
#include <utility>

// Definition of class TVector ==================================//
template <typename T>
TVector<T>::TVector() : capacity(SPARECAPACITY), size(0)
{
    array = new T[capacity]; // creates a new array with capacity = SPARECAPACITY
}

template <typename T>
TVector<T>::TVector(T val, int num) : capacity(SPARECAPACITY + num), size(num)
{
    array = new T[capacity];       // creates a new array with capacity = SPARECAPACITY + num
    for (int i = 0; i < size; i++) // sets each element of the array to val
        array[i] = val;
}

template <typename T>
TVector<T>::~TVector() // destructor
{
    if (array != nullptr) // if the array is not empty
        delete[] array;   // deallocates memory used for array

    size = 0;
    capacity = 0;
}

template <typename T>
TVector<T>::TVector(const TVector<T> &v) // copy constructor
{
    capacity = v.capacity;     // sets the capacity of the new array to the capacity
                               // of the input array
    size = v.size;             // sets the size of the new array to the size of the input
                               // array
    array = new T[v.capacity]; // creates a new copy of the input array

    for (int i = 0; i < size; i++)
        array[i] = std::move(v.array[i]); // moves the elements of the input array to the new array
}

template <typename T>
TVector<T> &TVector<T>::operator=(const TVector<T> &v) // copy assignment operator
{
    if (this != &v) // checks if the lhs and rhs point to different data
    {
        delete[] array;            // deallocates memory used for array
        capacity = v.capacity;     // sets the capacity of the new array to the
                                   // capacity of the input array
        size = v.size;             // sets the size of the new array to the size of the input
                                   // array
        array = new T[v.capacity]; // creates a new copy of the input array

        for (int i = 0; i < size; i++)
            array[i] = std::move(v.array[i]); // moves the elements of the input
                                              // array to the new array
    }
    return *this; // returns the new array
}

template <typename T>
TVector<T>::TVector(TVector<T> &&v) // move constructor
{
    capacity = v.capacity;     // sets the capacity of the new array to the capacity
                               // of the input array
    size = v.size;             // sets the size of the new array to the size of the input
                               // array
    array = new T[v.capacity]; // sets the new array to the input array

    for (int i = 0; i < size; i++)
        array[i] = std::move(v.array[i]); // moves the elements of the input array to the new array
}

template <typename T>
TVector<T> &TVector<T>::operator=(TVector<T> &&v) // move assignment operator
{
    if (this != &v)
    {
        delete[] array;            // deallocates memory used for array
        capacity = v.capacity;     // sets the capacity of the new array to the
                                   // capacity of the input array
        size = v.size;             // sets the size of the new array to the size of the input
                                   // array
        array = new T[v.capacity]; // sets the new array to the input array

        for (int i = 0; i < size; i++)
            array[i] = std::move(v.array[i]); // moves the elements of the input
                                              // array to the new array
    }
    return *this; // returns the new array
}

template <typename T>
bool TVector<T>::IsEmpty() const // checks to see whether container is empty
{
    return size == 0; // if size is 0 then the container is empty
}

template <typename T>
void TVector<T>::Clear() // clear out Vector, reset to empty
{
    size = 0;                 // sets the amount of elements of the array to 0
    capacity = SPARECAPACITY; // sets the capacity of the array to the original capacity
    array = new T[capacity];  // creates a new array with the original capacity
}

template <typename T>
int TVector<T>::GetSize() const // return the size of the vector
{
    return size;
}

template <typename T>
void TVector<T>::InsertBack(const T &d) // insert data d as last element
{
    if (size == capacity)              // if the array is full
        SetCapacity(2 * capacity + 1); // doubles the capacity of the array

    array[size++] = d; // sets the last element of the array and increments the size of the array
}

template <typename T>
void TVector<T>::RemoveBack() // remove last element of Vector
{
    if (size > 0) // if the vector is not empty
        size--;   // decrements the size of the array
}

template <typename T>
T &TVector<T>::GetFirst() const
{
    if (size == 0)                // if the vector is empty
        return TVector<T>::dummy; // returns an empty vector

    return array[0]; // returns the first element of the array
}

template <typename T>
T &TVector<T>::GetLast() const
{
    if (size == 0)                // if the vector is empty
        return TVector<T>::dummy; // returns an empty vector

    return array[size - 1]; // returns the last element of the array
}

template <typename T>
TVectorIterator<T> TVector<T>::GetIterator() const
{
    TVectorIterator<T> itr; // creates an iterator
    itr.index = 0;          // sets the index of the iterator to 0
    itr.vsize = size;       // sets the size of the iterator to the size of the array
    itr.ptr = array;        // sets the pointer of the iterator to the first element of the array

    return itr; // returns an iterator to the first element of the array
}

template <typename T>
TVectorIterator<T> TVector<T>::GetIteratorEnd() const
{
    TVectorIterator<T> itr;       // creates an iterator
    itr.index = size - 1;         // sets the index of the iterator to the last element of the array
    itr.vsize = size;             // sets the size of the iterator to the size of the array
    itr.ptr = array + (size - 1); // sets the pointer of the iterator to the last element of the array

    return itr; // returns an iterator to the last element of the array
}

template <typename T>
void TVector<T>::SetCapacity(unsigned int c)
{
    if (capacity < size) // if the capacity of the array is less than the size of the array
        return;          // then return

    T *newArray = new T[c]; // creates a new array with the new capacity

    for (int i = 0; i < size; i++)
        newArray[i] = std::move(array[i]); // moves the elements of the old array to the new array

    capacity = c;      // sets the capacity of the array to the new capacity
    delete[] array;    // deallocates memory used for array
    array = newArray; // swaps the old array with the new array
}

template <typename T>
TVectorIterator<T> TVector<T>::Insert(TVectorIterator<T> pos, const T &d)
{
    int position = pos.index; // sets the position of the iterator to the index of the iterator

    if (size == 0) // if the vector is empty
    {
        pos.index = 0;    // sets the index of the iterator to 0
        pos.vsize = size; // sets the size of the iterator to the size of the array
        pos.ptr = array;  // sets the pointer of the iterator to the first element of the array
        return pos;       // returns an iterator to the first element of the array
    }

    if (size == capacity)              // if the array is full
        SetCapacity(2 * capacity + 1); // doubles the capacity of the array

    for (int i = size - 1; i >= position; i--) // moves the elements of the array to the right
        array[i + 1] = std::move(array[i]);

    array[position] = d; // sets the element of the array to d
    size++;              // increments the size of the array

    pos.index = position;       // sets the index of the iterator to the position
    pos.vsize = size;           // sets the size of the iterator to the size of the array
    pos.ptr = array + position; // sets the pointer of the iterator to the position

    return pos; // returns an iterator to the position
}

template <typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos)
{
    int position = pos.index; // sets the position of the iterator to the index of the iterator
    int i = position;         // sets i to the position of the iterator

    for (i = position; i < size - 1; i++)
        array[i] = std::move(array[i + 1]); // moves the elements of the array to the left

    size--; // decrements the size of the array

    pos.index = position;       // sets the index of the iterator to the position
    pos.vsize = size;           // sets the size of the iterator to the size of the array
    pos.ptr = array + position; // sets the pointer of the iterator to the position

    return pos; // returns an iterator to the position
}

template <typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos1, TVectorIterator<T> pos2)
{
    int position1 = pos1.index;           // sets the position of the first iterator to the index of the first iterator
    int position2 = pos2.index;           // sets the position of the second iterator to the index of the second iterator
    int i = position1;                    // sets i to the position of the first iterator
    int k = position2;                    // sets k to the position of the second iterator
    int distance = position2 - position1; // sets distance to the difference between the positions

    for (i = position1; i < size - distance; i++)
        array[i] = std::move(array[k++]); // moves the elements of the array to the left

    size = i; // sets the size of the array to i

    TVectorIterator<T> pos; // creates an iterator
    pos.index = i;          // sets the index of the iterator to i
    pos.vsize = size;       // sets the size of the iterator to the size of the array
    pos.ptr = array + i;    // sets the pointer of the iterator to the position

    return pos; // returns an iterator to the position
}

template <typename T>
void TVector<T>::Print(std::ostream &os, char delim) const
{
    for (int i = 0; i < size; i++)
    {
        os << array[i] << delim; // prints the elements of the array
    }
}

template <typename T>
TVector<T> operator+(const TVector<T> &t1, const TVector<T> &t2)
{
    TVector<T> result; // creates a new vector

    // Insert elements from the first vector
    for (TVectorIterator<T> itr = t1.GetIterator(); itr.HasNext(); itr.Next())
        result.InsertBack(itr.GetData());

    // Insert elements from the second vector
    for (TVectorIterator<T> itr = t2.GetIterator(); itr.HasNext(); itr.Next())
        result.InsertBack(itr.GetData());

    return result; // returns the new vector
}

// Definition of class TVectorIterator ===========================//
template <typename T>
TVectorIterator<T>::TVectorIterator()
{
    ptr = nullptr; // sets the pointer of the iterator to null
    vsize = 0;     // sets the size of the iterator to 0
}

template <typename T>
bool TVectorIterator<T>::HasNext() const // next item available?
{
    return vsize >= index + 1;
}

template <typename T>
bool TVectorIterator<T>::HasPrevious() const // previous item available?
{
    return index > 0;
}

template <typename T>
TVectorIterator<T> TVectorIterator<T>::Next()
{
    if (HasNext()) // if the iterator has a next element
    {
        index++; // increments the index of the iterator
        ptr++;   // increments the pointer of the iterator
    }
    return *this; // returns the iterator
}

template <typename T>
TVectorIterator<T> TVectorIterator<T>::Previous()
{
    if (HasPrevious()) // if the iterator has a previous element
    {
        index--; // decrements the index of the iterator
        ptr--;   // decrements the pointer of the iterator
    }
    return *this; // returns the iterator
}

template <typename T>
T &TVectorIterator<T>::GetData() const
{
    if (index < 0 || index > vsize) // if the index of the iterator is less than 0 or
                                    // greater than the size of the iterator
        return TVector<T>::dummy;   // returns an empty vector

    return *ptr; // returns the element of the array
}
