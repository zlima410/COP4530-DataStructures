#include "bet.h"

/* PUBLIC */
BET::BET() : root{nullptr} {}; // default constructor

BET::BET(const string &postfix) : root{nullptr} // one parameter constructor that takes in postfix expression string
{
    buildFromPostFix(postfix); // call to buildFromPostfix
}

BET::BET(const BET &rhs) : root{nullptr} // copy constructor
{ 
    ClearStack();
    root = clone(rhs.root);
    betStack.push(root);
}

BET::~BET() // destructor
{
    if (!empty)
        makeEmpty(root);
    if (root != nullptr)
        delete root;
}

const BET &BET::operator=(const BET &rhs)   // assignment operator overload
{
    if (this != &rhs) // check for self assignment
    {
        if (!empty())
            makeEmpty(root);    // delete all nodes in the tree if it isn't empty

        root = clone(rhs.root); // clone the root

        ClearStack(); // make sure to empty stack

        betStack.push(root);
    }
    return *this;
}