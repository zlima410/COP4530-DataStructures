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
    size_t newSize = prime_below(size);
    if (newSize == 0)
        newSize = default_capacity;
    theLists.resize(newSize);
}

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
    // destructor
    clear();
}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K &k) const
{
    // check if key k exists in the hash table
    auto &whichList = theLists[myhash(k)];
    for (const auto &ele : whichList)
    {
        if (ele.first == k)
            return true;
    }
    return false;
}

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv) const
{
    // check if key-value pair kv exists in the hash table
    auto &whichList = theLists[myhash(kv.first)];
    for (const auto &ele : whichList)
    {
        if (ele == kv)
            return true;
    }
    return false;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> &kv)
{
    // insert kv into the hash table
    if (match(kv))
        return false;

    auto &whichList = theLists[myhash(kv.first)];

    for (auto &ele : whichList)
    {
        if (ele.first == kv.first)
        {
            ele.second = kv.second;
            return true;
        }
    }

    whichList.push_back(kv);

    if (++currentSize > theLists.size())
        rehash();

    return true;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> &&kv)
{
    // insert an rvalue kv into the hash table
    if (match(kv))
        return false;

    auto &whichList = theLists[myhash(kv.first)];
    for (auto &pair : whichList) {
        if (pair.first == kv.first) {
            pair.second = std::move(kv.second);
            return true;
        }
    }

    whichList.push_back(std::move(kv));

    if (++currentSize > theLists.size())
        rehash();

    return true;
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K &k)
{
    // remove the key k and its value from the hash table
    auto &whichList = theLists[myhash(k)];

    for (auto itr = whichList.begin(); itr != whichList.end(); ++itr)
    {
        if ((*itr).first == k)
        {
            whichList.erase(itr);
            --currentSize;
            return true;
        }
    }

    return false;
}

template <typename K, typename V>
void HashTable<K, V>::clear()
{
    // clear the hash table
    makeEmpty();
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename)
{
    // load key-value pairs from a file
    ifstream fh(filename);
    if (!fh.is_open())
        return false;
    }

    K key;
    V value;
    while (fh >> key >> value)
    {
        if (contains(key))
        {
            cerr << "Error: key " << key << " already exists." << endl;
            continue;
        }

        if (!insert(std::move(std::make_pair(key, value))))
        {
            cerr << "Error: unable to insert key-value pair." << endl;
            return false;
        }
    }

    fh.close();
    return true;
}

template <typename K, typename V>
void HashTable<K, V>::dump() const
{
    // print the contents of the hash table for debugging
    cout << "In dump, in total there are " << theLists.size() << " rows in the vector." << endl;
    for (size_t i = 0; i < theLists.size(); ++i)
    {
        cout << "v[" << i << "]:";
        if (!theLists[i].empty())
        {
            for (const auto &pair : theLists[i])
                cout << " " << pair.first << " " << pair.second;
        }
        cout << endl;
    }
}

template <typename K, typename V>
size_t HashTable<K, V>::size() const
{
    // return the current size of the hash table
    return currentSize;
}

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) const
{
    // write the key-value pairs of the hash table to a file
    ofstream fh(filename);
    if (!fh.is_open())
        return false;
    }

    for (const auto &theList : theLists)
    {
        for (const auto &kv : theList)
            fh << kv.first << " " << kv.second << endl;
    }
    fh.close();
    return true;
}

template <typename K, typename V>
void HashTable<K, V>::makeEmpty()
{
    // helper function to clear the hash table and preparing it for rehash or
    // destruction
    for (auto &thisList : theLists)
        thisList.clear();
    
    currentSize = 0;
}

template <typename K, typename V>
void HashTable<K, V>::rehash()
{
    // helper function to rehash the hash table when currentSize is larger than
    // the vector's size
    auto oldLists = std::move(theLists);
    theLists.resize(prime_below(2 * theLists.size()));
    for (auto &list : theLists)
        list.clear();

    currentSize = 0;
    for (auto &list : oldLists)
        for (auto &kv : list)
            insert(std::move(kv));
}

template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const
{
    // implement hash function
    static hash<K> hf;
    return hf(k) % theLists.size();
}
