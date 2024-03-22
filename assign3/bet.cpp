#include "bet.h"

/* PUBLIC */
BET::BET() : root{nullptr} {}; // default constructor

BET::BET(const string &postfix) : root{nullptr} // one parameter constructor that takes in postfix expression string
{
    buildFromPostfix(postfix); // call to buildFromPostfix
    cout << "Successfully built the tree given " << postfix << endl;
}

BET::BET(const BET &rhs) : root{nullptr} // copy constructor
{
    ClearStack();
    root = clone(rhs.root);
    betStack.push(root);
}

BET::~BET() // destructor
{
    if (!empty())
        makeEmpty(root);
    if (root != nullptr)
        delete root;
}

const BET & BET::operator=(const BET &rhs) // assignment operator overload
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

bool BET::buildFromPostfix(const string &postfix)
{
    if (!empty()) // make sure a new tree is being made
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

void BET::printInfixExpression() const {
    printInfixExpression(root);
    cout << endl;
}

void BET::printPostfixExpression() const {
    printPostfixExpression(root);
    cout << endl;
}

size_t BET::size() const {
    return size(root);
}

size_t BET::leaf_nodes() const {
    return leaf_nodes(root);
}

bool BET::empty() const {
    return {root == nullptr};
}

void BET::ClearStack() {
    while (!betStack.empty())   // pop each item in the stack while it isn't empty
        betStack.pop();
}

bool BET::isOperator(const string &s) const   // if string is an operator
{
    return (s == "+" || s == "-" || s == "/" || s == "*");
}

bool BET::isOperand(const string &s) const   // if string is an operand
{
    if (s.length() == 1) {
        char c = s[0];
        return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '_'));
    }
    else
        return true;
}

/* PRIVATE */

// print infix expression by navigating through tree by left, element, right
void BET::printInfixExpression(BET::BinaryNode *n) const {
    if (n != nullptr)
    {
        if (isOperator(n->element) && n != root)    // if node is an operator and not root node
            cout << "( ";
        printInfixExpression(n->left);
        cout << n->element << " ";
        printInfixExpression(n->right);

        if (isOperator(n->element) && n != root)
            cout << ") ";
    }
}

// print postfix expression by navigating through tree by left, right, element
void BET::printPostfixExpression(BET::BinaryNode *n) const
{
    if (n != nullptr) {
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        cout << n->element << " ";
    }
}

// frees memory allocated to a tree by recursively calling delete
void BET::makeEmpty(BinaryNode* &t) {
    if (t != nullptr)   // if node is not empty delete 
    {
        // make sure t is not a leaf node by checking if left and right are nullptr
        if (t->left != nullptr)
            makeEmpty(t->left);
        if (t->right != nullptr)
            makeEmpty(t->right);
        delete t;   // free the memory
    }

    t = nullptr;    // set t to nullptr to end recursion
}

// clone a given tree by recursively creating new nodes
BET::BinaryNode * BET::clone(BET::BinaryNode* t) const {
    if (t == nullptr)
        return nullptr;
    else
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
}

// return the number of nodes by counting recursively
size_t BET::size(BET::BinaryNode *t) const {
    if (t == nullptr)
        return 0;
    else
        return 1 + size(t->left) + size(t->right);
}

// return the number of leaf nodes by counting recursively
size_t BET::leaf_nodes(BET::BinaryNode *t) const {
    if (t == nullptr)
        return 0;
    
    // if the node has no childern it is a leaf node
    if (t->left == nullptr && t->right == nullptr)
        return 1;
    else
        return 0 + leaf_nodes(t->left) + leaf_nodes(t->right);
}