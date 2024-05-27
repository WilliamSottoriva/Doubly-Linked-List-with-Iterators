#include <iostream>
#include <utility>
#include <string>
#include "myList.hpp"
#include "myInteger.hpp"

// default constructor
template <typename T>
MyList<T>::MyList() {
  startNode = endNode = nullptr;
  listSize = 0;
  sentinel = new Node(); // empty node indicates sentinel value
}

// copy constructor
// deep copy  all elements from other to this
template <typename T>
MyList<T>::MyList(const MyList& other) : MyList() {
  for (Node* n = other.startNode; n != other.sentinel; n = n->next) {
    push_back(n->data);
  }
}


// assignment operator
// uses copy and swap idiom
template <typename T>
MyList<T>& MyList<T>::operator=(MyList other) {
  if (this != &other) { // prevent self assignment to avoid null dereference
    std::swap(startNode, other.startNode);
    std::swap(endNode, other.endNode);
    std::swap(listSize, other.listSize);
    std::swap(sentinel, other.sentinel);
  }
  return *this;
}

// destructor
// free all memory allocated with new
template <typename T>
MyList<T>::~MyList() {
  emptyList();
}

// clears all elements in list
template <typename T>
void MyList<T>::emptyList(){
  while (!empty()) {
    pop_front();
  }
  delete sentinel;
}

// constructor from an initializer list
// This lets us create a list with the ints 1,2,3,4 by saying
// MyList<int> li {1,2,3,4};
template <typename T>
MyList<T>::MyList(std::initializer_list<T> vals) : MyList() {
  for (const T& val : vals) {
    push_back(val);
  }
}

// push back
// add an element to the back of the list
template <typename T>
void MyList<T>::push_back(T val) {
  Node* n = new Node(val, nullptr, sentinel); // n->prev initially set to nullptr
  if (empty()) { // check if list is empty to avoid null dereference
    startNode = n;
  } else {
    n->prev = endNode;
    endNode->next = n;
  }
  endNode = n;
  sentinel->prev = endNode;
  listSize++;
}

// pop back
// remove the last element
template <typename T>
void MyList<T>::pop_back() {
  if (!empty()) { // ensure list is not empty to avoid null dereference
    Node* temp = endNode; // store node being removed
    if (startNode == endNode) { // if list contains one element handle differently
      startNode = endNode  = nullptr;
      sentinel->prev = nullptr;
    } else {
      endNode = endNode->prev;
      endNode->next = sentinel;
      sentinel->prev = endNode;
    }
    delete temp; // avoids memory leak
    listSize--;
  }
}

// push front
// add an element to the front of the list
template <typename T>
void MyList<T>::push_front(T val) {
  Node* n = new Node(val, nullptr, nullptr);
  if (empty()) { // check if list is empty to avoid null dereference
    endNode = n;
    endNode->next = sentinel;
  } else {
    n->next = startNode;
    startNode->prev = n;
  }
  startNode = n;
  listSize++;
}

// pop front
// remove the first element
template <typename T>
void MyList<T>::pop_front() {
  if (!empty()) { // ensure list is not empty to avoid null dereference
    Node* temp = startNode; // store node being removed
    if (startNode == endNode) { // if list contains one element handle differently
      startNode = endNode = nullptr;
      sentinel->prev = nullptr;
    } else {
      startNode = startNode->next;
      startNode->prev = nullptr;
    }
    delete temp; // avoids memory leak
    listSize--;
  }
}

// return the first element by reference
template <typename T>
T& MyList<T>::front() {
  if(empty()) {
    throw std::runtime_error("List is empty");
  }
  return startNode->data;
}

// return the first element by const reference
// this one can be used on a const MyDeque
template <typename T>
const T& MyList<T>::front() const {
  if(empty()) {
    throw std::runtime_error("List is empty");
  }
  return startNode->data;
}

// return the last element by reference
template <typename T>
T& MyList<T>::back() {
  if(empty()) {
    throw std::runtime_error("List is empty");
  }
  return endNode->data;
}

// return the last element by const reference
// this one can be used on a const MyDeque
template <typename T>
const T& MyList<T>::back() const {
  if(empty()) {
    throw std::runtime_error("List is empty");
  }
  return endNode->data;
}

// is the list empty?
template <typename T>
bool MyList<T>::empty() const {
  return startNode == nullptr;
}

// return the number of elements in the list
template <typename T>
int MyList<T>::size() const {
  return listSize;
}

// return an iterator pointing to the first element
template <typename T>
typename MyList<T>::Iterator MyList<T>::begin() const {
    return Iterator(startNode);
}

// getter method for current_
template <typename T>
typename MyList<T>::Node* MyList<T>::Iterator::getCurrent() const {
  return current_;
}

// return an Iterator that does not point to any element in the list.
// This serves as a sentinel for having reached past the end of the list.template <typename T>
template <typename T>
typename MyList<T>::Iterator MyList<T>::end() const {
    return Iterator(sentinel);
}

// insert an element into the linked list before *it with the value val
template <typename T>
void MyList<T>::insert(const Iterator& it, const T& val) {
  if(it.getCurrent() == startNode) { // handle start node using existing method for edge cases
    push_front(val);
  } else if (it.getCurrent() == sentinel) { // handle end node using existing method for edge cases
    push_back(val);
  } else { 
    // initialise new node
    Node* n = new Node(val,it.getCurrent()->prev, it.getCurrent());
    // insert new node
    it.getCurrent()->prev->next = n;
    it.getCurrent()->prev = n;
    listSize++;
  }
}

// remove *it from the list
template <typename T>
void MyList<T>::erase(const Iterator& it) {
  if (it.getCurrent() == startNode) { // handle start node using existing method for edge cases
    pop_front();
  } else if (it.getCurrent() == endNode) { // handle end node using existing method for edge cases
    pop_back();
  } else {
    // remove pointers to it node
    it.getCurrent()->prev->next = it.getCurrent()->next;
    it.getCurrent()->next->prev = it.getCurrent()->prev;
    delete it.getCurrent(); // delete it node to avoid memory leak
    listSize--;
  } 
}

// Iterator constructor
template <typename T>
MyList<T>::Iterator::Iterator(Node* pointer) {
  current_ = pointer;
}

// (pre-)increment an iterator
template <typename T>
typename MyList<T>::Iterator& MyList<T>::Iterator::operator++() {
    if (current_ == nullptr || current_->next == nullptr) {
      throw std::runtime_error("Incrementing null");
    } else {
      current_ = current_->next;
    }
    return *this;
}

// (pre-)decrement an iterator
template <typename T>
typename MyList<T>::Iterator& MyList<T>::Iterator::operator--() {
    if (current_ == nullptr || current_->prev == nullptr) {
      throw std::runtime_error("Decrementing null");
    }
    else {
      current_ = current_->prev;
    }
    return *this;
}

// return the value pointed at by an iterator
template <typename T>
T& MyList<T>::Iterator::operator*() const {
    if (current_ == nullptr) {
      throw std::runtime_error("Dereferencing null");
    }
    return current_->data;
}

// These lines let the compiler know with which types we will be
// instantiating MyList
template class MyList<int>;
template class MyList<std::string>;
template class MyList<MyInteger>;
