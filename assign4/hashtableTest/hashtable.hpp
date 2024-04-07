#include "hashtable.h"

template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below(unsigned long n)
{
    if (n > max_prime)
    {
        std::cerr << "** input too large for prime_below()\n";
        return 0;
    }
    if (n == max_prime)
    {
        return max_prime;
    }
    if (n <= 1)
    {
        std::cerr << "** input too small \n";
        return 0;
    }

    // now: 2 <= n < max_prime
    std::vector<unsigned long> v(n + 1);
    setPrimes(v);
    while (n > 2)
    {
        if (v[n] == 1)
            return n;
        --n;
    }

    return 2;
}

template <typename K, typename V>
void HashTable<K, V>::setPrimes(vector<unsigned long> &vprimes)
{
    int i = 0;
    int j = 0;

    vprimes[0] = 0;
    vprimes[1] = 0;
    int n = vprimes.capacity();

    for (i = 2; i < n; ++i)
        vprimes[i] = 1;

    for (i = 2; i * i < n; ++i)
    {
        if (vprimes[i] == 1)
            for (j = i + i; j < n; j += i)
                vprimes[j] = 0;
    }
}

template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size)
{
    // constructor
    // initialize vector with size or default_capacity based on given size
    size_t tableSize = prime_below(size);
    if (tableSize == 0)
        tableSize = default_capacity;

    theList.resize(tableSize);
    currentSize = 0;
}

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
    // destructor
}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K &k) const
{
    // check if key k exists in the hash table
}

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv) const
{
    // check if key-value pair kv exists in the hash table
}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> &kv)
{
    // insert kv into the hash table
}

template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> &&kv)
{
    // insert a rvalue kv into the hash table
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K &k)
{
    // remove the key k and its value from the hash table
}

template <typename K, typename V>
void HashTable<K, V>::clear()
{
    // clear the hash table
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename)
{
    // load key-value pairs from a file
}

template <typename K, typename V>
void HashTable<K, V>::dump() const
{
    // print the contents of the hash table for debugging
}

template <typename K, typename V>
size_t HashTable<K, V>::size() const
{
    // return the current size of the hash table
}

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) const
{
    // write the key-value pairs of the hash table to a file
}

template <typename K, typename V>
void HashTable<K, V>::makeEmpty()
{
    // helper function to clear the hash table and preparing it for rehash or destruction
}

template <typename K, typename V>
void HashTable<K, V>::rehash()
{
    // helper function to rehash when the hash table exceeds threshold
}

template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const
{
    // implement hash function
}