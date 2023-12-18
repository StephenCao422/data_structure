/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <iostream>
using namespace std;

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here

    Node* y = t->right;
    t->right = y->left;
    y->left = t;
    t = y;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* y = t->left;
    t->left = y->right;
    y->right = t;
    t = y;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}


template <class K, class V>
int AVLTree<K, V>::height(Node* t) const {
    if (!t) return -1; 
    int leftHeight = height(t->left);
    int rightHeight = height(t->right);
    return 1 + std::max(leftHeight, rightHeight);
}


template <class K, class V>
int AVLTree<K, V>::balanceFactor(Node* t) const {
    if (!t) return 0;
    return height(t->left) - height(t->right);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int balance = balanceFactor(subtree);
    if (balance > 1) {
        if (balanceFactor(subtree->left) < 0) {
            rotateLeftRight(subtree);
        } else {
            rotateRight(subtree);
        }
    } else if (balance < -1) {
        if (balanceFactor(subtree->right) > 0) {
            rotateRightLeft(subtree);
        } else {
            rotateLeft(subtree);
        }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (!subtree) {
        subtree = new Node(key, value);
        return;
    }

    if (key < subtree->key) {
        insert(subtree->left, key, value);
    } else if (key > subtree->key) {
        insert(subtree->right, key, value);
    } else {
        subtree->value = value;
        return;
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = nullptr;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
             Node* temp = subtree->left;
            while (temp->right) {
                temp = temp->right;
            }
            subtree->key = temp->key;
            subtree->value = temp->value;
            remove(subtree->left, temp->key);
        } else {
            /* one-child remove */
            // your code here
                        Node* temp = subtree;
            if (subtree->left) {
                subtree = subtree->left;
            } else {
                subtree = subtree->right;
            }
            delete temp;
        }
        // your code here
    }
    if (!subtree) return;
    rebalance(subtree);
}
