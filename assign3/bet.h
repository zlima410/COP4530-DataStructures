#ifndef BET_H
#define BET_H
#include <stack>
#include <string>
using namespace std;

class BET {
    private:
        struct BinaryNode {
            string element;
            BinaryNode *left;
            BinaryNode *right;

            // constructor
            BinaryNode() : left{nullptr}, right{nullptr}{}
            BinaryNode(const string &elm, BinaryNode *ll, BinaryNode *rr)
                : element{elm}, left{ll}, right{rr}{}
        };

    public:
        BET();                      // default constructor
        BET(const string postfix);  // tree constructor
        BET(const BET&);            // copy constructor
        ~BET();                     // destructor

        // mutators
        const BET &operator=(const BET &);  // assignment operator overload
        bool buildFromPostFix(const string postfix);    // test if the tree built successfully

        // accessors
        int size();     // number of nodes in the tree
        int leaf_nodes; // number of leaf nodes in the tree
        bool empty();   // test if the tree is empty
};

#endif