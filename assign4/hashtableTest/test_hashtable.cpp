#include "hashtable.h"

int main()
{
    cop4530::HashTable<int, int> h;
    h.dump();
    h.~HashTable();
    return 0;
}