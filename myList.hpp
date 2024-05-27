#ifndef MY_LIST_HPP_
#define MY_LIST_HPP_

#include <initializer_list>

template <typename T>
class MyList  {
 public:
  struct Node {
    T data {};
    Node* prev {nullptr};
    Node* next {nullptr};
    Node(T input_data = T {}, Node* prevNode = nullptr, 
      Node* nextNode = nullptr) : data {input_data}, prev {prevNode}, 
                                  next {nextNode} {} 
  };

  class Iterator {
    // useful reference
    // https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
   private: 
    Node* current_;
  
   public:
    // construct an Iterator from a pointer to a Node
    Iterator(Node*); 
    // advance an iterator to the next Node (pre-increment)
    Iterator& operator++();
    // move iterator to previous node (pre-decrement)
    Iterator& operator--();
    // return value at the node pointed to by the iterator
    T& operator*() const;

    // test if two iterators are equal
    friend bool operator==(const Iterator& a, const Iterator& b) {
      return a.current_ == b.current_;
    }
    // test if two iterators are not equal
    friend bool operator!=(const Iterator& a, const Iterator& b) {
      return not (a == b);
    }

    Node* getCurrent() const;
  };

 // Declare some member variables 
 private:
  Node* startNode;
  Node* endNode;
  Node* sentinel; // Sentinel value used to indicate end of list
  int listSize;

 public:
  // Default Constructor
  // Do some setup of your list architecture?
  MyList(); 

  // Construct a list from an initializer list
  // This lets us create a list with the ints 1,2,3,4 by saying
  // MyList<int> li {1,2,3,4};
  MyList(std::initializer_list<T> vals);

  // Copy Constructor
  MyList(const MyList&); 

  // Operator=
  MyList& operator=(MyList); 

  // Destructor
  // free all memory allocated with new
  ~MyList();
 
  // return the first element by reference
  T& front();
  // return the first element by const reference
  // this one can be used on a const MyList
  const T& front() const;

  // return the last element by reference
  T& back();
  // return the last element by const reference
  // this one can be used on a const MyList
  const T& back() const;

  // add an element to the front of the list
  void push_front(T);
  // remove the first element
  void pop_front();

  // add an element to the back of the list
  void push_back(T);
  // remove the last element
  void pop_back();

  // add an element to the list before the node pointed to by the Iterator
  void insert(const Iterator&, const T&);
  // remove the element of the list pointed to by the Iterator
  void erase(const Iterator&);

  // does the list have any elements?
  bool empty() const;
  // return the number of elements in the list
  int size() const;

  // return an Iterator pointing to the first element
  Iterator begin() const;
  // return an Iterator that does not point to any element in the list.
  // This serves as a sentinel for having reached past the end of the list
  Iterator end() const;

  // Clears all elements in the list
  void emptyList();
};

#endif    // MY_LIST_HPP_
