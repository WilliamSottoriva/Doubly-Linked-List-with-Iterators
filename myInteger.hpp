#ifndef MY_INTEGER_HPP_
#define MY_INTEGER_HPP_

#include <iostream>
#include <vector>

class MyInteger {
 private:
  int value {};

 public:
  // default constructor
  MyInteger() {}

  // constructor from an int
  // member initialisation list
  explicit MyInteger(int input) : value {input} {}

  // copy constructor
  MyInteger(const MyInteger& x) : value {x.value} {}

  // assignment operator
  MyInteger& operator=(const MyInteger& x) {
    value = x.value;
    return *this;
  }

  // pre-increment operator
  MyInteger& operator++() {
    ++value;
    return *this;
  }

  // destructor
  ~MyInteger() {}

  // determine if two MyIntegers are equal
  // friend is not a member function of MyInteger
  // ensures  x == y if and only y == x
  friend bool operator==(const MyInteger& x, const MyInteger& y) {
    return x.value == y.value;
  }

  // determine if one MyInteger is less than another
  friend bool operator<(const MyInteger& x, const MyInteger& y) {
    return x.value < y.value;
  }

  friend std::ostream& operator<<(std::ostream& out, const MyInteger& x) {
    out << x.value;
    return out;
  }
};

#endif    // MY_INTEGER_HPP_
