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

// NUMBER DOUBLY LINKED LIST NAMESPACE
namespace numberDLL
{
  const int nIndex = 6;
  const int nDigits = 10;
}

// NUMBER DOUBLY LINKED LIST CLASS

template <class NodeType>
class NumberDoublyLinkedList : public DoublyLinkedList<NodeType>
{
protected:
  // Protected Methods
  void print(DoublyNodePtr<NodeType>);
  void printReverse(DoublyNodePtr<NodeType>);
  NodeType total(DoublyNodePtr<NodeType>);
  NodeType max(DoublyNodePtr<NodeType>);
  bool linearSearch(DoublyNodePtr<NodeType>, NodeType);

public:
  // Inherit Constructors
  using DoublyLinkedList<NodeType>::DoublyLinkedList;

  // Constructors
  NumberDoublyLinkedList() : DoublyLinkedList<NodeType>(-1){};

  // Public Methods
  void print() { return print(this->head); };                                // Set Head Node as p Node
  void printReverse() { return printReverse(this->tail); };                  // Set Tail Node as p Node
  NodeType total() { return total(this->head); };                            // Set Head Node as p Node
  NodeType max() { return max(this->head); };                                // ...
  bool linearSearch(NodeType key) { return linearSearch(this->head, key); }; // ...

  int compare(int, int);
  NumberSingleLinkedList<NodeType> *SingleLinkedList();
};

// Method to Print Nodes from Head to Tail
template <class NodeType>
void NumberDoublyLinkedList<NodeType>::print(DoublyNodePtr<NodeType> p)
{
  int n = 0;

  // Prints Header
  cout << left << setw(numberDLL::nIndex) << setfill(' ') << "Index"
       << setw(numberDLL::nDigits + 1) << setfill(' ') << "Node"
       << '\n';

  // Prints from Head to Tail
  while (p != NULL)
  {
    cout << setw(numberDLL::nIndex) << setfill(' ') << n++
         << setw(numberDLL::nDigits + 1) << setfill(' ') << p->data
         << '\n';
    p = p->next;
  }
}

// Method to Print Nodes from Tail to Head
template <class NodeType>
void NumberDoublyLinkedList<NodeType>::printReverse(DoublyNodePtr<NodeType> p)
{
  int n = this->length - 1;

  // Prints Header
  cout << left << setw(numberDLL::nIndex) << setfill(' ') << "Index"
       << setw(numberDLL::nDigits + 1) << setfill(' ') << "Node"
       << '\n';

  // Prints from Tail to Head
  while (p != NULL)
  {
    cout << setw(numberDLL::nIndex) << setfill(' ') << n--
         << setw(numberDLL::nDigits + 1) << setfill(' ') << p->data
         << '\n';
    p = p->prev;
  }
}

// Method that Returns the Sum of All Node's Data Field
template <class NodeType>
NodeType NumberDoublyLinkedList<NodeType>::total(DoublyNodePtr<NodeType> p)
{
  NodeType sum = 0;

  while (p != NULL)
  {
    sum += p->data;
    p = p->next;
  }

  return sum;
}

// Method that Returns the Highest Number in Linked List
template <class NodeType>
NodeType NumberDoublyLinkedList<NodeType>::max(DoublyNodePtr<NodeType> p)
{
  static NodeType m = -1;

  while (p != NULL)
  {
    // Node Number Value is Bigger
    if (p->data > m)
      m = p->data;

    p = p->next;
  }

  return m;
}

// Method that Checks if the Given Number is Inside Linked List
template <class NodeType>
bool NumberDoublyLinkedList<NodeType>::linearSearch(DoublyNodePtr<NodeType> p, NodeType key)
{
  while (p != NULL)
  {
    if (key == p->data)
      return true;

    p = p->next;
  }

  return false;
}

// Method to Compare Two Nodes Values
template <class NodeType>
int NumberDoublyLinkedList<NodeType>::compare(int index1, int index2)
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
    return this->error; // One or Both Indexes don't Exist

  if (value1 == value2)
    return 0;

  return value1 > value2 ? 1 : 2;
}

// Method to Create Single Linked List
template <class NodeType>
NumberSingleLinkedList<NodeType> *NumberDoublyLinkedList<NodeType>::SingleLinkedList()
{
  NumberSingleLinkedList<NodeType> *copy = new NumberSingleLinkedList<NodeType>(this->error);

  DoublyNodePtr<NodeType> p = this->head;

  while (p != NULL)
  {
    copy->insertionSort(p->data);
    p = p->next;
  }
  return copy;
}

#endif