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
        BET(const string& postfix); // tree constructor
        BET(const BET&);            // copy constructor
        ~BET();                     // destructor

        // mutators
        const BET & operator=(const BET &);               // assignment operator overload
        bool buildFromPostfix(const string& postfix);    // test if the tree built successfully

        // accessors
        size_t size() const;       // number of nodes in the tree
        size_t leaf_nodes() const; // number of leaf nodes in the tree
        bool empty() const;        // test if the tree is empty

        void printInfixExpression() const;
        void printPostfixExpression() const;

    private:
        stack<BinaryNode*> betStack;    // stack used by the binary expression tree
        BinaryNode *root;               // bet's root node

        void ClearStack();
        bool isOperator(const string &s) const;
        bool isOperand(const string &s) const;

        // recursive functions
        void printInfixExpression(BinaryNode *n) const;   // print the infix expression
        void makeEmpty(BinaryNode* &t);                   // delete all nodes in the subtree and call the destructor
        void printPostfixExpression(BinaryNode *n) const; // print the postfix expression

        BinaryNode *clone(BinaryNode *t) const; // clone all nodes and call the assignment operator overload
        size_t size(BinaryNode *t) const;             // number of nodes in the subtree of t
        size_t leaf_nodes(BinaryNode *t) const;       // number of leaf nodes in the subtree t
};

#endif