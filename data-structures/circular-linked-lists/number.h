#include <cstdlib>
#include <iostream>
#include <string>
#include <limits.h>
#include <iomanip>

#include "base.h"

using std::cout;
using std::left;
using std::setfill;
using std::setw;
using std::string;

#ifndef NUMBER_CIRCULAR_LINKED_LISTS
#define NUMBER_CIRCULAR_LINKED_LISTS

// NUMBER LINKED LIST CLASS

template <class T>
class NumberCircularLinkedList : public CircularLinkedList<T>
{
public:
  // Inherit Constructors
  using CircularLinkedList<T>::CircularLinkedList;

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
};

// Method to Print Nodes from Tail to Head
template <class T>
void NumberCircularLinkedList<T>::print(DoublyNodePtr<T> p)
{
  int n = 0;

  // Prints from Head to Tail
  cout << setw(6) << left << setfill(' ') << "Index" << setw(10) << "Node" << '\n';
  do
  {
    cout << setw(6) << n++ << p->data << '\n';
    p = p->next;
  } while (p != this->head);
}

// Method Overload
template <class T>
void NumberCircularLinkedList<T>::print()
{
  this->print(this->head); // Set Head Node as p Node
}

// Method to Print Nodes from Tail to Head
template <class T>
void NumberCircularLinkedList<T>::printReverse(DoublyNodePtr<T> p)
{
  int n = this->length - 1;

  // Prints from Tail to Head
  cout << setw(6) << left << setfill(' ') << "Index" << setw(10) << "Node" << '\n';
  do
  {
    cout << setw(6) << n-- << p->data << '\n';
    p = p->prev;
  } while (p != this->tail);
}

// Method Overload
template <class T>
void NumberCircularLinkedList<T>::printReverse()
{
  this->printReverse(this->tail); // Set Head Node as p Node
}

// Method that Returns the Sum of All Node's Data Field
template <class T>
T NumberCircularLinkedList<T>::total(DoublyNodePtr<T> p)
{
  T sum = 0;

  do
  {
    sum += p->data;
    p = p->next;
  } while (p != this->head);

  return sum;
}

// Method Overload
template <class T>
T NumberCircularLinkedList<T>::total()
{
  return this->total(this->head); // Set Head Node as p Node
}

// Method that Returns the Highest Number in Linked List
template <class T>
T NumberCircularLinkedList<T>::max(DoublyNodePtr<T> p)
{
  static T m = -1;

  do
  {
    // Node Number Value is Bigger
    if (p->data > m)
      m = p->data;

    p = p->next;
  } while (p != this->head);

  return m;
}

// Method Overload
template <class T>
T NumberCircularLinkedList<T>::max()
{
  return this->max(this->head); // Set Head Node as p Node
}

// Method that Checks if the Given Number is Inside Linked List
template <class T>
DoublyNodePtr<T> NumberCircularLinkedList<T>::linearSearch(DoublyNodePtr<T> p, T key)
{
  do
  {
    if (key == p->data)
      return p;

    p = p->next;
  } while (p != this->head);

  return NULL;
}

// Method Overload
template <class T>
DoublyNodePtr<T> NumberCircularLinkedList<T>::linearSearch(T key)
{
  return this->linearSearch(this->head, key); // Set Head Node as p Node
}

// Method to Compare Two Nodes Values
template <class T>
int NumberCircularLinkedList<T>::compare(int index1, int index2)
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

#endif