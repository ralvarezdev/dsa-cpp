#include <cstdlib>
#include <iostream>
#include <string>
#include <limits.h>
#include <iomanip>

#include "base.h"
#include "../single-linked-lists/number.h"

using std::cout;
using std::left;
using std::setfill;
using std::setw;
using std::string;

#ifndef NUMBER_DOUBLY_LINKED_LISTS
#define NUMBER_DOUBLY_LINKED_LISTS

// NUMBER LINKED LIST CLASS

template <class T>
class NumberDoublyLinkedList : public DoublyLinkedList<T>
{
public:
  // Inherit Constructors
  using DoublyLinkedList<T>::DoublyLinkedList;

  // Public Methods
  void print();
  void print(DoublyNodePtr<T>);
  void printReverse();
  void printReverse(DoublyNodePtr<T>);
  T total();
  T total(DoublyNodePtr<T>);
  T max();
  T max(DoublyNodePtr<T>);
  DoublyNodePtr<T> linearSearch(T);
  DoublyNodePtr<T> linearSearch(DoublyNodePtr<T>, T);
  int compare(int, int);
  NumberSingleLinkedList<T> SingleLinkedList();
};

// Method to Print Nodes from Tail to Head
template <class T>
void NumberDoublyLinkedList<T>::print(DoublyNodePtr<T> p)
{
  int n = 0;

  // Prints from Head to Tail
  cout << setw(6) << left << setfill(' ') << "Index" << setw(10) << "Node" << '\n';
  while (p != NULL)
  {
    cout << setw(6) << n++ << p->data << '\n';
    p = p->next;
  }
}

// Method Overload
template <class T>
void NumberDoublyLinkedList<T>::print()
{
  this->print(this->head); // Set Head Node as p Node
}

// Method to Print Nodes from Tail to Head
template <class T>
void NumberDoublyLinkedList<T>::printReverse(DoublyNodePtr<T> p)
{
  int n = this->length - 1;

  // Prints from Tail to Head
  cout << setw(6) << left << setfill(' ') << "Index" << setw(10) << "Node" << '\n';
  while (p != NULL)
  {
    cout << setw(6) << n-- << p->data << '\n';
    p = p->prev;
  }
}

// Method Overload
template <class T>
void NumberDoublyLinkedList<T>::printReverse()
{
  this->printReverse(this->tail); // Set Head Node as p Node
}

// Method that Returns the Sum of All Node's Data Field
template <class T>
T NumberDoublyLinkedList<T>::total(DoublyNodePtr<T> p)
{
  T sum = 0;

  while (p != NULL)
  {
    sum += p->data;
    p = p->next;
  }

  return sum;
}

// Method Overload
template <class T>
T NumberDoublyLinkedList<T>::total()
{
  return this->total(this->head); // Set Head Node as p Node
}

// Method that Returns the Highest Number in Linked List
template <class T>
T NumberDoublyLinkedList<T>::max(DoublyNodePtr<T> p)
{
  static T m = -1;

  while (p != NULL)
  {
    // Node Number Value is Bigger
    if (p->data > m)
      m = p->data;

    p = p->next;
  }

  return m;
}

// Method Overload
template <class T>
T NumberDoublyLinkedList<T>::max()
{
  return this->max(this->head); // Set Head Node as p Node
}

// Method that Checks if the Given Number is Inside Linked List
template <class T>
DoublyNodePtr<T> NumberDoublyLinkedList<T>::linearSearch(DoublyNodePtr<T> p, T key)
{
  while (p != NULL)
  {
    if (key == p->data)
      return p;

    p = p->next;
  }

  return NULL;
}

// Method Overload
template <class T>
DoublyNodePtr<T> NumberDoublyLinkedList<T>::linearSearch(T key)
{
  return this->linearSearch(this->head, key); // Set Head Node as p Node
}

// Method to Compare Two Nodes Values
template <class T>
int NumberDoublyLinkedList<T>::compare(int index1, int index2)
{
  /*
  Possible Results:

  -1: One or Both Nodes are NULL
  0: Nodes Data are Equal
  1: Node1 Data is Greater than Node2 Data
  2: Node2 Data is Greater than Node1 Data

  */

  T value1, value2;

  value1 = this->get(index1);
  value2 = this->get(index2);

  if (value1 == this->error || value2 == this->error)
    return -1; // One or Both Indexes don't Exist

  if (index1 == index2)
    return 0;

  return index1 > index2 ? 1 : 2;
}

// Method to Create Single Linked List
template <class T>
NumberSingleLinkedList<T> NumberDoublyLinkedList<T>::SingleLinkedList()
{
  NumberSingleLinkedList<T> copy(this->error);

  DoublyNodePtr<T> p = this->head;

  while (p != NULL)
  {
    copy.insertionSort(p->data);
    p = p->next;
  }
  return copy;
}

#endif