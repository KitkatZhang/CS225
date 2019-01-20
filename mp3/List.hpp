/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */


/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */




template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(nullptr);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  _destroy();

}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode *p = head_;
  ListNode *q = head_;
  while(p != tail_){
    q = p;
    p = p -> next;
    delete q;
  }
  delete p;
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
  /// @todo Graded in MP3.1
  if(head_ != nullptr){
    ListNode * temp = head_;
    head_ = new ListNode(ndata);
    head_ -> next = temp;
    temp -> prev = head_;
    head_ -> prev = nullptr;
  }else{
    head_ = new ListNode(ndata);
    head_ -> next = nullptr;
    head_ -> prev = nullptr;
    tail_ = head_;
  }
  length_ ++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  if(head_ != nullptr){
    ListNode * temp = tail_;
    temp -> next = new ListNode(ndata);
    tail_ = temp -> next;
    tail_ -> prev = temp;
    tail_ -> next = nullptr;
  }else{
    head_ = new ListNode(ndata);
    head_ -> next = nullptr;
    head_ -> prev = nullptr;
    tail_ = head_;
  }
  length_ ++;
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
  /// @todo Graded in MP3.1
  if(startPoint == nullptr || endPoint == nullptr || startPoint == endPoint){
    return;
  }else{
    ListNode * tempprev = startPoint -> prev;
    ListNode * tempnext = endPoint -> next;
    ListNode * temphead = startPoint;
    ListNode * p = endPoint;
    ListNode * q;
    startPoint = endPoint;
    endPoint = temphead;
    while(p != tempprev){
      q = p -> next;
      p -> next = p -> prev;
      p -> prev = q;
      p = p -> next;
    }
    startPoint -> prev = tempprev;
    endPoint -> next = tempnext;
    if(tempprev != nullptr){
      tempprev -> next = startPoint;
    }else{
      head_ = startPoint;
    }
    if(tempnext != nullptr){
      tempnext -> prev = endPoint;
    }else{
      tail_ = endPoint;
    }
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  if(head_ == nullptr || tail_ == nullptr || head_ == tail_){
    return;
  }else{
    ListNode * p = head_;
    ListNode * q = head_;
    ListNode * temp = head_;
    while(p != nullptr){
      for(int i = 0; i < n - 1; i ++){
        p = p -> next;
        if(p == nullptr){
          reverse(temp, q);
          break;
        }
        q = q -> next;
      }
      if(p == nullptr){
        break;
      }
      reverse(temp, p);
      p = p -> next;
      q = p;
      temp = p;
    }
  }
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
  /// @todo Graded in MP3.1
  if(head_ == nullptr || tail_ == nullptr || head_ == tail_){
    return;
  }else{
    ListNode * p = head_;
    ListNode * q = head_;
    while(p -> next != tail_){
      p = p -> next;
      tail_ -> next = p;
      p -> prev = tail_;
      tail_ = p;
      q -> next = p -> next;
      p -> next -> prev = q;
      p -> next = nullptr;
      q = q -> next;
      p = q;
    }
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
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
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  ListNode * p;
  ListNode * q = start;
  for(int i = 0; i < splitPoint - 1; i ++){
    q = q -> next;
    if(q == nullptr){
      return nullptr;
    }
  }
  p = q -> next;
  q -> next = nullptr;
  return p;
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
  /// @todo Graded in MP3.2
  if(second == nullptr){
    return first;
  }else if(first == nullptr){
    first = second;
    second = nullptr;
    return first;
  }else{
    ListNode * fin;
    ListNode * p = first;
    ListNode * q = second;
    second = nullptr;
    fin = (p -> data) < (q -> data) ? p : q;
    first = (p -> data) < (q -> data) ? p : q;
    while(p != nullptr || q != nullptr){
      if(p != nullptr && q != nullptr){
          if(fin == p){
            p = p -> next;
          }else if(fin == q){
            q = q -> next;
          }
          if(p != nullptr && q != nullptr){
            fin -> next = (p -> data) < (q -> data) ? p : q;
            fin = fin -> next;
          }else if(p == nullptr){
            fin -> next = q;
            return first;
          }else if(q == nullptr){
            fin -> next = p;
            return first;
          }
      }
    }
  }
  return first;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  // Base case:
  if(chainLength == 0 || chainLength == 1){
    return start;
  }
  int midlength = chainLength / 2;
  ListNode * p = start;
  ListNode * q = p;
  for(int i = 0; i < midlength - 1; i++){
    p = p -> next;
  }
  q = p;
  p = p -> next;
  q -> next = nullptr;
  ListNode * left = mergesort(start, midlength);
  ListNode * right = mergesort(p, chainLength - midlength);
  ListNode * sortedlist = merge(left, right);
  return sortedlist;
}
