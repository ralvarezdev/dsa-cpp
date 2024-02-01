#include <cstdlib>

#include "base.h"

#ifndef NUMBER_LINKED_LISTS
#define NUMBER_LINKED_LISTS

// NUMBER LINKED LIST CLASS

template <class T>
class NumberLinkedList : public LinkedList<T>
{
public:
  // Inherit Constructors
  using LinkedList<T>::LinkedList;

  // Public Methods
  void print();
  void print(NodePtr<T>);
  void printReverse();
  void printReverse(NodePtr<T>);
  T total();
  T total(NodePtr<T>);
  T max();
  T max(NodePtr<T>);
  NodePtr<T> linearSearch(T);
  NodePtr<T> linearSearch(NodePtr<T>, T);
};

#endif