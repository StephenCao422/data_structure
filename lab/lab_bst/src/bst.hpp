/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    Node*& foundNode = find(root, key);
    return foundNode->value;
} 

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if (subtree == nullptr) {
        return subtree;
    } else if (subtree->key == key) {
        return subtree;
    } else {
        if (key < subtree->key) {
            return find(subtree->left, key);
        } else {
            return find(subtree->right, key);
        }
    }
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    insert(root, key, value);
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == nullptr) {
        subtree = new Node(key, value);
        return;
    }
    if (subtree->key == key) {
        return;
    }
    if (key < subtree->key) {
        insert(subtree->left, key, value);
    }
    else {
        insert(subtree->right, key, value);
    }
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    std::swap(first->key, second->key);
    std::swap(first->value, second->value);
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    remove(root, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
    if (!subtree) return;

    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else { 
        if (!subtree->left && !subtree->right) {
            delete subtree;
            subtree = nullptr;
        } else if (!subtree->left) {
            Node* temp = subtree->right;
            delete subtree;
            subtree = temp;
        } else if (!subtree->right) {
            Node* temp = subtree->left;
            //subtree = subtree->left;
            //delete temp;
            delete subtree;
            subtree = temp;
        } else {
            Node*& successor = findMax(subtree->left);
            swap(subtree, successor);
            remove(subtree->left, successor->key);
        }
    }
}

template <class K, class V>
typename BST<K, V>::Node*& BST<K, V>::findMax(Node*& subRoot) {
    if (subRoot->right) {
        return findMax(subRoot->right);
    }
    return subRoot;
}


template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K, V> tree;
    for (const auto& [key, value] : inList) {
        tree.insert(key, value);
    }
    return tree;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::vector<int> histogram(inList.size(), 0);
    std::sort(inList.begin(), inList.end());

    do {
        BST<K, V> tree = listBuild(inList);
        int h = tree.height();
        if(h >= 0){
            histogram[h]++;
        }
    } while (std::next_permutation(inList.begin(), inList.end()));

    return histogram;
}