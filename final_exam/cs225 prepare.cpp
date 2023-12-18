class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

//目标value的个数

class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() : root(nullptr) {}

    int countOccurrences111(TreeNode* node, int target) {
        if (node == nullptr) {
            return 0;
        }
        
        int count = 0;

        if (node->data == target) {
            count = 1;
        }
        
        
        return count + countOccurrences111(node->left, target) + countOccurrences111(node->right, target);
    
    }

    int countOccurrences(int target) {
        return countOccurrences111(root, target);
    }
};

// number of leaves
int countLeafNodes() {
    return count(root);
}
int count(Node* node) {
    if (!node) {
        return 0;
    }
    if (!node->left && !node->right) {
        return 1;
    }
    return count(node->left)+count(node->right);
}


// fulltree or not
#include<iostream>

template<typename T>
struct Node {
    T data;
    Node* left;
    Node* right;

    Node(const T& data) : data(data), left(nullptr), right(nullptr) {}
};

template<typename T>
class BinaryTree {
public:
    Node<T>* root;

    BinaryTree() : root(nullptr) {}

    bool isFull() {
        return ::isFull(root);
    }
};

template<typename T>
bool isFull(Node<T>* node) {
    if (node == nullptr) {
        return true;
    }

    if ((node->left == nullptr) != (node->right == nullptr)) {
        return false;
    }

    return isFull(node->left) && isFull(node->right);
}

// exam


template<typename T>
class BinaryTree {
public:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(const T& data) : data(data), left(nullptr), right(nullptr) {}
    };

    Node* root;

    BinaryTree() : root(nullptr) {}

    void insert(const T& data) {
        // Your existing insertion logic goes here
    }

    int calculateHeight() const {
        return calculateHeight(root);
    }


    int calculateHeight(Node* node) const {
        if (node == nullptr) {
            return -1;
        }

        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);

        return std::max(leftHeight, rightHeight)+1;
    }
}; 
//









/*
template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)

    Node* y = t->right;   // Get the right child of t
    t->right = y->left;   // Make the left child of y the new right child of t
    y->left = t;          // t becomes the left child of y

    // Update heights
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    y->height = 1 + std::max(heightOrNeg1(y->left), heightOrNeg1(y->right));

    t = y;  // Make y the new root
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

    Node* y = t->left;
    t->left = y->right;
    y->right = t;

    
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));

    y->height = 1 + std::max(heightOrNeg1(y->left), heightOrNeg1(y->right));

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
void AVLTree<K, V>::rebalance(Node*& t)
{
    int balance = heightOrNeg1(t->left) - heightOrNeg1(t->right);

    if (balance > 1)  
    {
        if (heightOrNeg1(t->left->right) > heightOrNeg1(t->left->left))
        {
            rotateLeftRight(t);
        }else{
        rotateRight(t);
        }
    }
    else if (balance < -1)  
    {
        if (heightOrNeg1(t->right->left) > heightOrNeg1(t->right->right))
        {
            rotateRightLeft(t);
        }else{
        rotateLeft(t);
        }
    }

    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}
*/
