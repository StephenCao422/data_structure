
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return currentIdx*2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return currentIdx*2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return currentIdx / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    //return false;
    if(currentIdx*2 >= _elems.size())
      return false;
    else
      return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    //return 0;
    size_t left = leftChild(currentIdx);
    size_t right = rightChild(currentIdx);

    //if only left child exists (indexing starts at 1)
    if (right >= _elems.size()) {
        return left;
    }
    //return the index of the child with the higher priority
    return higherPriority(_elems[left], _elems[right]) ? left : right;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    //check if current node has at least one child
    if (hasAChild(currentIdx)) {
        size_t childIdx = maxPriorityChild(currentIdx);
        //if the child has higher priority, swap and continue heapifying down
        if (higherPriority(_elems[childIdx], _elems[currentIdx])) {
            std::swap(_elems[currentIdx], _elems[childIdx]);
            heapifyDown(childIdx);
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm

    //start with a dummy as the heap is 1-indexed
    _elems.push_back(T());

    for (const auto& e : elems) {
        _elems.push_back(e);
    }

    //build the heap by "heapifying" from the last parent to the root
    for (size_t i = parent(_elems.size() - 1); i >= root(); i--) {
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    //return T();

    // ensure the heap is not empty
    if (empty()) {
        throw std::logic_error("pop from empty heap");
    }

    T highestPriorityElement = _elems[root()];
    _elems[root()] = _elems.back(); // move the last element to the root
    _elems.pop_back();

    heapifyDown(root()); // restore heap property

    return highestPriorityElement;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return T();
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // corrects the heap to remain as a valid heap even after update
    if (idx >= _elems.size() || idx < root()) {
        throw std::logic_error("index out of bounds");
    }

    _elems[idx] = elem;

    // decide whether to heapify up or down based on the new element
    if (idx > root() && higherPriority(_elems[idx], _elems[parent(idx)])) {
        heapifyUp(idx);
    } else {
        heapifyDown(idx);
    }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    //return true;
    return _elems.size() == 1;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
