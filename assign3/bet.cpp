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

const BET &BET::operator=(const BET &rhs) // assignment operator overload
{
    if (this != &rhs) // check for self assignment
    {
        if (!empty())
            makeEmpty(root); // delete all nodes in the tree if it isn't empty

        root = clone(rhs.root); // clone the root

        ClearStack(); // make sure to empty stack

        betStack.push(root);
    }
    return *this;
}

bool BET::buildFromPostFix(const string &postfix)
{
    if (!empty) // make sure a new tree is being made
    {
        makeEmpty(root);
        ClearStack();
    }

    bool ret = true;
    string post = postfix, token;

    for (string::iterator itr = post.begin(); itr != post.end(); ++itr)
    {
        token += *itr; // add the current character to the token string

        if (*itr == ' ' || itr == (post.end() - 1)) // create the tree if the character is the end or a space
        {
            if (*itr == ' ') // if the last character is a space remove it
                token.pop_back();
            if (isOperand(token))
            {
                BinaryNode *n = new BinaryNode(token, nullptr, nullptr); // create a new node with the operand
                betStack.push(n);                                        // push new node into the stack
            }
            else if (isOperator(token)) // if the token is an operator
            {
                BinaryNode *rt, *lt; // right and left temporary nodes
                if (!betStack.empty())  // if the stack is not empty
                {
                    rt = betStack.top();
                    betStack.pop();
                }
                else {
                    ret = false;
                    break;
                }

                if (!betStack.empty())  // if the stack is not empty
                {
                    lt = betStack.top();
                    betStack.pop();
                }
                else {
                    ret = false;
                    break;
                }

                BinaryNode *op = new BinaryNode(token, lt, rt); // create a new node with operators and operands
                betStack.push(op);                              // push the new node into the stack
            }
            token = ""; // reset the token string
        }
    }

    if (!betStack.empty())
    {
        root = betStack.top(); 

        if (betStack.size() > 1 && isOperand(root->element))    // if the stack has leftover operands
            ret = false;
    }
    else 
        ret = false;

    if (!ret) {
        cout << "Wrong postfix expression" << endl;

        if (!empty())   // clear attempted tree
        {
            makeEmpty(root);
            ClearStack();
        }
    }
    return ret;
}