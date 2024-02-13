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

template <class NodeType>
class NumberDoublyLinkedList : public DoublyLinkedList<NodeType>
{
public:
  // Inherit Constructors
  using DoublyLinkedList<NodeType>::DoublyLinkedList;

  // Constructors
  NumberDoublyLinkedList() : DoublyLinkedList<NodeType>(-1){};

  // Public Methods
  void print();
  void print(DoublyNodePtr<NodeType>);
  void printReverse();
  void printReverse(DoublyNodePtr<NodeType>);
  NodeType total();
  NodeType total(DoublyNodePtr<NodeType>);
  NodeType max();
  NodeType max(DoublyNodePtr<NodeType>);
  DoublyNodePtr<NodeType> linearSearch(NodeType);
  DoublyNodePtr<NodeType> linearSearch(DoublyNodePtr<NodeType>, NodeType);
  int compare(int, int);
  NumberSingleLinkedList<NodeType> SingleLinkedList();
};

// Method to Print Nodes from Tail to Head
template <class NodeType>
void NumberDoublyLinkedList<NodeType>::print(DoublyNodePtr<NodeType> p)
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
template <class NodeType>
void NumberDoublyLinkedList<NodeType>::print()
{
  this->print(this->head); // Set Head Node as p Node
}

// Method to Print Nodes from Tail to Head
template <class NodeType>
void NumberDoublyLinkedList<NodeType>::printReverse(DoublyNodePtr<NodeType> p)
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
template <class NodeType>
void NumberDoublyLinkedList<NodeType>::printReverse()
{
  this->printReverse(this->tail); // Set Head Node as p Node
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

// Method Overload
template <class NodeType>
NodeType NumberDoublyLinkedList<NodeType>::total()
{
  return this->total(this->head); // Set Head Node as p Node
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

// Method Overload
template <class NodeType>
NodeType NumberDoublyLinkedList<NodeType>::max()
{
  return this->max(this->head); // Set Head Node as p Node
}

// Method that Checks if the Given Number is Inside Linked List
template <class NodeType>
DoublyNodePtr<NodeType> NumberDoublyLinkedList<NodeType>::linearSearch(DoublyNodePtr<NodeType> p, NodeType key)
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
template <class NodeType>
DoublyNodePtr<NodeType> NumberDoublyLinkedList<NodeType>::linearSearch(NodeType key)
{
  return this->linearSearch(this->head, key); // Set Head Node as p Node
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
    return -1; // One or Both Indexes don't Exist

  if (index1 == index2)
    return 0;

  return index1 > index2 ? 1 : 2;
}

// Method to Create Single Linked List
template <class NodeType>
NumberSingleLinkedList<NodeType> NumberDoublyLinkedList<NodeType>::SingleLinkedList()
{
  NumberSingleLinkedList<NodeType> copy(this->error);

  DoublyNodePtr<NodeType> p = this->head;

  while (p != NULL)
  {
    copy.insertionSort(p->data);
    p = p->next;
  }
  return copy;
}

#endif