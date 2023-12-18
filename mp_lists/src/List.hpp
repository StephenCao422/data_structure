/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(nullptr);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
  if(head_ == NULL){
    return;
  }
  ListNode* ptr = head_;
  ListNode* cur = nullptr;
  while(ptr != nullptr){
    cur = ptr;
    ptr = ptr->next;
    delete cur;
  }
  head_ = nullptr;
  tail_ = nullptr;
}
/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  head_ = newNode;
  length_++;


}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode* newNode = new ListNode(ndata);
  newNode->prev = tail_;
  newNode->next = NULL;
  if (tail_ != NULL)
  {
    tail_->next = newNode;
  }
  if (head_ == NULL)
  {
    head_ = newNode;
  }
  tail_ = newNode;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in mp_lists part 1

  ListNode * curr = start;
  if(splitPoint == 0){
    start = NULL;
    return curr;
  }
  if(splitPoint > length_){
    return NULL;
  }
  if(start == NULL){
    return NULL;
  }
  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    if(curr->next!= NULL){
      curr = curr->next;
    }
  }
  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
      // return curr;
  }

  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in part 1
  if (!head_ || !head_->next) return;


  ListNode* current = head_;
  ListNode* tail = head_;
  
  while (tail->next) {
    tail = tail->next;
  }

  while (current->next != tail && current->next != nullptr) {
    ListNode* toMove = current->next;
    current->next = toMove->next;
    if (toMove->next) {
      toMove->next->prev = current;
    }
    tail->next = toMove;
    toMove->prev = tail;
    toMove->next = nullptr;
    tail = toMove;

    if (!current->next) break;
      current = current->next;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in mp_lists part 2
    if ((startPoint == endPoint)||(startPoint==NULL && endPoint==NULL)) {
      return;
    }
    ListNode* left = startPoint->prev;
    ListNode* right = endPoint->next;
    ListNode* currentNode = startPoint;
    ListNode* tempNode = startPoint;
    ListNode* originStart = startPoint;
    ListNode* originEnd = endPoint;

    while (currentNode != endPoint) {
        tempNode = currentNode->prev;
        currentNode->prev = currentNode->next;
        currentNode->next = tempNode;
        currentNode = currentNode->prev;
    }
    // correct the next pointers of the new startPoint and endPoint
    startPoint->next = endPoint->next;
    currentNode->next = currentNode->prev;
    currentNode->prev = startPoint->prev;

    // fix the pointers of nodes just before startPoint and just after endPoint
    if (left != NULL) {
        left->next = endPoint;
    } else {
        head_ = endPoint; // update head if startPoint was head
    }

    if (right != NULL) {
        right->prev = startPoint;
    } else {
        tail_ = startPoint; // update tail if endPoint was tail
    }

    // swap startPoint and endPoint references
    startPoint = originEnd;
    endPoint = originStart;
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in mp_lists part 2
    if (n <= 1) return;  // reversing blocks of size 1 or less has no effect

    ListNode* startPoint = head_;
    ListNode* endPoint = head_;

    while (startPoint != nullptr) {
        // move the endpoint n-1 steps (or until the end of the list)
        for (int i = 0; i < n - 1 && endPoint->next != nullptr; ++i) {
            endPoint = endPoint->next;
        }

        ListNode* nextStartPoint = endPoint->next;

        // reverse the block
        reverse(startPoint, endPoint);

        // if this is the first block, update the head of the list
        if (startPoint->prev == nullptr) {
            head_ = startPoint;
        }

        // if this is the last block, update the tail of the list
        if (endPoint->next == nullptr) {
            tail_ = endPoint;
        }

        // move to the next block
        startPoint = nextStartPoint;
        endPoint = nextStartPoint;
    }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in mp_lists part 2
    ListNode* head; // this will point to the head of the merged list
    ListNode* tail; // this will point to the current tail of the merged list

    if (!first) return second; 
    if (!second) return first;

    // initialize head and tail pointers based on the first node of each list
    if (first->data < second->data) {
        head = tail = first;
        first = first->next;
    } else {
        head = tail = second;
        second = second->next;
    }

    while (first && second) {
        if (first->data < second->data) {
            tail->next = first;
            first->prev = tail;
            tail = first;
            first = first->next;
        } else {
            tail->next = second;
            second->prev = tail;
            tail = second;
            second = second->next;
        }
    }

    // if there are remaining nodes in either list, append them to the merged list
    if (first) {
        tail->next = first;
        first->prev = tail;
    } else if (second) {
        tail->next = second;
        second->prev = tail;
    }

    // update the prev pointer of the head to nullptr
    head->prev = nullptr;

    return head;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in mp_lists part 2
    // Base case: if the chainLength is 1 or 0, the chain is already sorted
    if (chainLength <= 1) {
        return start;
    }

    // Step 1: find the middle of the chain to divide the chain into two halves
    ListNode* middle = start;
    for (int i = 0; i < chainLength / 2 - 1; ++i) {
        middle = middle->next;
    }
    
    // Step 2: recursively sort the two halves
    ListNode* secondHalfStart = middle->next;
    middle->next = nullptr; // Disconnect the two halves
    if (secondHalfStart) secondHalfStart->prev = nullptr;
    
    ListNode* left = mergesort(start, chainLength / 2);
    ListNode* right = mergesort(secondHalfStart, chainLength - chainLength / 2);

    // Step 3: merge the sorted halves back together
    return merge(left, right);
}
