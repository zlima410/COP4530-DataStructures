#include "hashtable.h"
#include <iostream>
#include <string>

using namespace std;
using namespace cop4530;

int main()
{
    // create a hash table instance
    HashTable<int, string> hashTable;

    // test insert
    hashTable.insert(make_pair(1, "one"));
    hashTable.insert(make_pair(2, "two"));
    hashTable.insert(make_pair(3, "three"));

    // test contains
    cout << "Contains key 2: " << (hashTable.contains(2) ? "Yes" : "No") << endl;

    // test match
    cout << "Match key-value (2, 'two'): " << (hashTable.match(make_pair(2, "two")) ? "Yes" : "No") << endl;

    // test dump
    cout << "Initial hash table:" << endl;
    hashTable.dump();

    // test remove
    hashTable.remove(2);
    cout << "After removing key 2:" << endl;
    hashTable.dump();

    // test clear
    hashTable.clear();
    cout << "After clearing the hash table:" << endl;
    hashTable.dump();

    hashTable.load("input.txt"); 
    cout << "After loading from file:" << endl;
    hashTable.dump();

    hashTable.write_to_file("output.txt");
    cout << "Hash table written to output.txt" << endl;

    return 0;
}