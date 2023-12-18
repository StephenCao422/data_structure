/**
 * @file binarytree.hpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "InorderTraversal.h"
#include <iostream>
#include <stack>
using namespace std;

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror(){
    //your code heres
    mirror(root);
    std::cout << std::endl;
    return;
}

template <typename T>
void BinaryTree<T>::mirror(Node* root){
    if (root == nullptr) {
        return;
    }
    if(root->left != NULL){
      mirror(root->left);
    }
    if(root->right != NULL){
      mirror(root->right);
    }
    Node* ptr = root->left;
    root->left = root->right;
    root->right = ptr;

    // mirror(root->left);
    // mirror(root->right);
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    if (!root) return true;
    
    std::stack<Node*> nodeStack;
    Node* current = root;
    Node* prev = nullptr;
    
    while (current || !nodeStack.empty()) {
        while (current) {
            nodeStack.push(current);
            current = current->left;
        }
        current = nodeStack.top();
        nodeStack.pop();
        if (prev && current->elem <= prev->elem) {
            return false;
        }
        prev = current;
        current = current->right;
    }
    
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    Node* prev = nullptr;
    return isOrderedHelper(root, prev);
}

template <typename T>
bool BinaryTree<T>::isOrderedHelper(Node* current, Node*& prev) const
{
    if (current == nullptr) {
        return true;
    }
    if (!isOrderedHelper(current->left, prev)) {
        return false;
    }
    if (prev != nullptr && current->elem <= prev->elem) {
        return false;
    }
    prev = current;
    return isOrderedHelper(current->right, prev);
}