#pragma once
#ifndef BST_H
#define BST_H

#include "WordEntry.h"
//#include "WordEntry.cpp"
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

template <typename T>
struct Node
{
    T key;
    Node *left;
    Node *right;
    WordEntry *wordEntry;
    Node() : key(0), left(NULL), right(NULL), wordEntry(NULL) {}
    Node(string word) : key(word), left(NULL), right(NULL), wordEntry(new WordEntry(word)) {}
};

template <typename T>
class BST
{
private:
    Node<T> *root;
    long size;
    bool duplicatesAllowed;

public:
    BST<T>();
    BST<T>(bool duplicatesAllowed);
    ~BST<T>();
    Node<T> *getRoot();
    Node<T> *insert(string data);
    Node<T> *insert(string data, long frequency);
    bool remove(T data);
    bool elementExists(T data);
    Node<T> *find(T data);
    T *toArr();
    void empty();
    long length();
    void printInOrder();
};

template <typename T>
BST<T>::BST()
{
    this->root = NULL;
    this->size = 0;
    this->duplicatesAllowed = false;
}

template <typename T>
BST<T>::BST(bool duplicatesAllowed)
{
    this->root = NULL;
    this->size = 0;
    this->duplicatesAllowed = duplicatesAllowed;
}

template <typename T>
BST<T>::~BST()
{
    empty();
}

template <typename T>
Node<T> *BST<T>::getRoot()
{
    return root;
}

template <typename T>
Node<T> *BST<T>::insert(string data)
{
    Node<T> *newNode = new Node<T>(data);
    if (root == NULL)
    {
        root = newNode;
        size++;
        return newNode;
    }

    Node<T> *curr = root;
    Node<T> *prev;
    while (curr)
    {
        prev = curr;
        if (data == curr->key && !duplicatesAllowed)
        {
            return curr;
        }
        else if (data <= curr->key)
        {
            curr = curr->left;
        }
        else // if (data > curr->key)
        {
            curr = curr->right;
        }
    }

    if (data <= prev->key)
    {
        prev->left = newNode;
    }
    else // if (data > prev->key)
    {
        prev->right = newNode;
    }
    size++;
    return newNode;
}

template <typename T>
Node<T> *BST<T>::insert(string data, long frequency)
{
    Node<T> *newNode = new Node<T>(data);
    newNode->wordEntry->setFrequency(frequency);
    if (root == NULL)
    {
        root = newNode;
        size++;
        return newNode;
    }

    Node<T> *curr = root;
    Node<T> *prev;
    while (curr)
    {
        prev = curr;
        if (frequency == curr->wordEntry->getFrequency() && !duplicatesAllowed)
        {
            return curr;
        }
        else if (frequency <= curr->wordEntry->getFrequency())
        {
            curr = curr->left;
        }
        else // if (frequency > curr->wordEntry->getFrequency())
        {
            curr = curr->right;
        }
    }

    if (frequency <= prev->wordEntry->getFrequency())
    {
        prev->left = newNode;
    }
    else // if (frequency > prev->wordEntry->getFrequency())
    {
        prev->right = newNode;
    }
    size++;
    return newNode;
}

template <typename T>
bool BST<T>::remove(T data)
{
    Node<T> *curr = root;
    Node<T> *prev = root;
    bool found = false;
    while (curr)
    {
        if (data == curr->key)
        {
            found = true;
            break;
        }
        prev = curr;
        if (data < curr->key)
        {
            curr = curr->left;
        }
        else
        { // if (data > curr.key)
            curr = curr->right;
        }
    }
    if (!found)
    {
        return false;
    }
    if (!curr->left && !curr->right) // node is a leaf
    {
        if (prev->left == curr)
        {
            prev->left = NULL;
        }
        else
        {
            prev->right = NULL;
        }
    }
    else if (curr->left && !curr->right)
    { // node has one child (left)
        if (prev->left == curr)
        {
            prev->left = curr->left;
        }
        else
        {
            prev->right = curr->left;
        }
        delete curr;
    }
    else if (!curr->left && curr->right)
    { // node has one child (right)
        if (prev->left == curr)
        {
            prev->left = curr->right;
        }
        else
        {
            prev->right = curr->right;
        }
        delete curr;
    }
    else
    { // node has two children
        // find predecessor (rightmost child in left subtree)
        Node<T> *predecessor = curr->left;
        Node<T> *parentOfPredecessor = curr;
        while (predecessor->right)
        {
            parentOfPredecessor = predecessor;
            predecessor = predecessor->right;
        }
        // copy predecessor's key to curr, then delete predecessor
        curr->key = predecessor->key;
        delete predecessor;
        if (parentOfPredecessor == curr)
        { // that means the while loop never executed
            parentOfPredecessor->left = NULL;
        }
        else
        {
            parentOfPredecessor->right = NULL;
        }
        // reinstate the BST invariant
        T temp;
        while (curr->key < curr->left->key || curr->key > curr->right->key)
        {
            if (curr->key < curr->left->key)
            {
                // swap
                temp = curr->key;
                curr->key = curr->left->key;
                curr->left->key = temp;
                curr = curr->left;
            }
            else
            { // if (curr->key > curr->right->key)
                // swap
                temp = curr->key;
                curr->key = curr->right->key;
                curr->right->key = temp;
                curr = curr->right;
            }
        }
    }
    size--;
    return true;
}

template <typename T>
bool BST<T>::elementExists(T data)
{
    if (find(data))
    {
        return true;
    }
    return false;
}

template <typename T>
Node<T> *BST<T>::find(T data)
{
    Node<T> *curr = root;
    while (curr)
    {
        if (data == curr->key)
        {
            return curr;
        }
        else if (data < curr->key)
        {
            curr = curr->left;
        }
        else
        { // if (data > curr->key)
            curr = curr->right;
        }
    }
    return NULL;
}

template <typename T>
T *BST<T>::toArr()
// in-order traversal
{
    T *arr = new T[size];
    int i = 0;
    Node<T> *curr = root;
    vector<Node<T> *> stack;
    while (curr || !stack.empty())
    {
        while (curr != NULL)
        {
            stack.push_back(curr);
            curr = curr->left;
        }
        curr = stack.back();
        stack.pop_back();
        arr[i] = curr->key;
        i++;
        curr = curr->right;
    }
    return arr;
}

template <typename T>
void BST<T>::empty()
// post order traversal
{
    vector<Node<T> *> stack;
    Node<T> *curr = root;
    while (curr || !stack.empty())
    {
        while (curr != NULL)
        {
            if (curr->right)
            {
                stack.push_back(curr->right);
            }
            stack.push_back(curr);
            curr = curr->left;
        }
        curr = stack.back();
        stack.pop_back();
        if (curr->right == stack.back())
        {
            stack.pop_back();
            stack.push_back(curr);
            curr = curr->right;
        }
        else
        {
            delete curr;
            curr = NULL;
        }
    }
    size = 0;
    root = NULL;
}

template <typename T>
long BST<T>::length()
{
    return size;
}

/* curr serves two functions: 
 * In the first part of the while loop, it moves down the left side of the tree, pushing all the nodes to the stack
 * In the second part of the while loop, it gets the element at the top of the stack, prints it, then moves to the right child
 */
template <typename T>
void BST<T>::printInOrder()
{
    vector<Node<T> *> stack;
    Node<T> *curr = root;
    while (curr || !stack.empty())
    {
        while (curr != NULL)
        {
            stack.push_back(curr);
            curr = curr->left;
        }
        curr = stack.back();
        stack.pop_back();
        cout << curr->key << endl;
        curr = curr->right;
    }
}

#endif
