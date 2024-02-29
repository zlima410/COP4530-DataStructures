#ifndef BET_H
#define BET_H
#include <iostream>
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
            BinaryNode(const string &theElement, BinaryNode *lt, BinaryNode *rt)
                : element{theElement}, left{lt}, right{rt}{}
            BinaryNode(string && theElement, BinaryNode *lt, BinaryNode *rt)
                : element{theElement}, left{lt}, right{rt}{}
        };

    public:
        BET();                      // default constructor
        BET(const string& postfix);  // tree constructor
        BET(const BET&);            // copy constructor
        ~BET();                     // destructor

        // mutators
        const BET &operator=(const BET &);  // assignment operator overload
        bool buildFromPostFix(const string& postfix);    // test if the tree built successfully

        // accessors
        size_t size();     // number of nodes in the tree
        size_t leaf_nodes(); // number of leaf nodes in the tree
        bool empty();   // test if the tree is empty

    private:
        stack<BinaryNode*> betStack;    // stack used by the binary expression tree
        BinaryNode *root;               // bet's root node

        void ClearStack();
        bool isOperator(const string &s);
        bool isOperand(const string &s);

        // recursive functions
        void printInfixExpression(BinaryNode *n);   // print the infix expression
        void makeEmpty(BinaryNode* &t);             // delete all nodes in the subtree and call the destructor
        void printPostfixExpression(BinaryNode *n); // print the postfix expression

        BinaryNode *clone(BinaryNode *t) const; // clone all nodes and call the assignment operator overload
        size_t size(BinaryNode *t);             // number of nodes in the subtree of t
        size_t leaf_nodes(BinaryNode *t);       // number of leaf nodes in the subtree t
};

#endif