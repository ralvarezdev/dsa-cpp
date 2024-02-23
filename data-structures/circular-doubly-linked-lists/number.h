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

#ifndef NUMBER_CIRCULAR_DOUBLY_LINKED_LISTS
#define NUMBER_CIRCULAR_DOUBLY_LINKED_LISTS

// NUMBER CIRCULAR DOUBLY LINKED LIST NAMESPACE
namespace numberCDLL
{
  const int nIndex = 6;
  const int nDigits = 10;
}

// NUMBER CIRCULAR DOUBLY LINKED LIST CLASS

template <class NodeType>
class NumberCircularDoublyLinkedList : public CircularDoublyLinkedList<NodeType>
{
protected:
  // Protected Methods
  void print(DoublyNodePtr<NodeType>);
  void printReverse(DoublyNodePtr<NodeType>);
  NodeType total(DoublyNodePtr<NodeType>);
  NodeType max(DoublyNodePtr<NodeType>);
  DoublyNodePtr<NodeType> linearSearch(DoublyNodePtr<NodeType>, NodeType);

public:
  // Inherit Constructors
  using CircularDoublyLinkedList<NodeType>::CircularDoublyLinkedList;

  // Constructors
  NumberCircularDoublyLinkedList() : CircularDoublyLinkedList<NodeType>(-1){};

  // Public Methods
  void print() { print(this->head); };                                                          // Set Head Node as p Node
  void printReverse() { printReverse(this->head->prev); };                                      // ...
  NodeType total() { return total(this->head); };                                               // ...
  NodeType max() { return max(this->head); };                                                   // ...
  DoublyNodePtr<NodeType> linearSearch(NodeType key) { return linearSearch(this->head, key); }; // ...

  int compare(int, int);
};

// Method to Print Nodes from Head to Tail
template <class NodeType>
void NumberCircularDoublyLinkedList<NodeType>::print(DoublyNodePtr<NodeType> p)
{
  int n = 0;

  // Prints Header
  cout << left << setw(numberCDLL::nIndex) << setfill(' ') << "Index"
       << setw(numberCDLL::nDigits + 1) << setfill(' ') << "Node"
       << '\n';

  // Prints from Head to Tail
  do
  {
    cout << setw(numberCDLL::nIndex) << setfill(' ') << n++
         << setw(numberCDLL::nDigits + 1) << setfill(' ') << p->data
         << '\n';
    p = p->next;
  } while (p != this->head);
}

// Method to Print Nodes from Tail to Head
template <class NodeType>
void NumberCircularDoublyLinkedList<NodeType>::printReverse(DoublyNodePtr<NodeType> p)
{
  int n = this->length - 1;

  // Prints Header
  cout << left << setw(numberCDLL::nIndex) << setfill(' ') << "Index"
       << setw(numberCDLL::nDigits + 1) << setfill(' ') << "Node"
       << '\n';

  // Prints from Tail to Head
  do
  {
    cout << setw(numberCDLL::nIndex) << setfill(' ') << n--
         << setw(numberCDLL::nDigits + 1) << setfill(' ') << p->data
         << '\n';
    p = p->prev;
  } while (p != this->head->prev);
}

// Method that Returns the Sum of All Node's Data Field
template <class NodeType>
NodeType NumberCircularDoublyLinkedList<NodeType>::total(DoublyNodePtr<NodeType> p)
{
  NodeType sum = 0;

  do
  {
    sum += p->data;
    p = p->next;
  } while (p != this->head);

  return sum;
}

// Method that Returns the Highest Number in Linked List
template <class NodeType>
NodeType NumberCircularDoublyLinkedList<NodeType>::max(DoublyNodePtr<NodeType> p)
{
  static NodeType m = -1;

  do
  {
    // Node Number Value is Bigger
    if (p->data > m)
      m = p->data;

    p = p->next;
  } while (p != this->head);

  return m;
}

// Method that Checks if the Given Number is Inside Linked List
template <class NodeType>
DoublyNodePtr<NodeType> NumberCircularDoublyLinkedList<NodeType>::linearSearch(DoublyNodePtr<NodeType> p, NodeType key)
{
  do
  {
    if (key == p->data)
      return p;

    p = p->next;
  } while (p != this->head);

  return NULL;
}

// Method to Compare Two Nodes Values
template <class NodeType>
int NumberCircularDoublyLinkedList<NodeType>::compare(int index1, int index2)
{
  /*
  Possible Results:

  -1: One or Both Nodes are NULL
  0: Nodes Data are Equal
  1: Node1 Data is Greater than Node2 Data
  2: Node2 Data is Greater than Node1 Data

  */

  NodeType value1, value2;

  value1 = this->get(index1);
  value2 = this->get(index2);

  if (value1 == this->error || value2 == this->error)
    return -1; // One or Both Indexes don't Exist

  if (index1 == index2)
    return 0;

  return index1 > index2 ? 1 : 2;
}

#endif