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

template <class NodeType>
class NumberCircularLinkedList : public CircularLinkedList<NodeType>
{
public:
  // Inherit Constructors
  using CircularLinkedList<NodeType>::CircularLinkedList;

  // Constructors
  NumberCircularLinkedList() : CircularLinkedList<NodeType>(-1){};

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
};

// Method to Print Nodes from Tail to Head
template <class NodeType>
void NumberCircularLinkedList<NodeType>::print(DoublyNodePtr<NodeType> p)
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
template <class NodeType>
void NumberCircularLinkedList<NodeType>::print()
{
  this->print(this->head); // Set Head Node as p Node
}

// Method to Print Nodes from Tail to Head
template <class NodeType>
void NumberCircularLinkedList<NodeType>::printReverse(DoublyNodePtr<NodeType> p)
{
  int n = this->length - 1;

  // Prints from Tail to Head
  cout << setw(6) << left << setfill(' ') << "Index" << setw(10) << "Node" << '\n';
  do
  {
    cout << setw(6) << n-- << p->data << '\n';
    p = p->prev;
  } while (p != this->head->prev);
}

// Method Overload
template <class NodeType>
void NumberCircularLinkedList<NodeType>::printReverse()
{
  this->printReverse(this->head->prev); // Set Head Node as p Node
}

// Method that Returns the Sum of All Node's Data Field
template <class NodeType>
NodeType NumberCircularLinkedList<NodeType>::total(DoublyNodePtr<NodeType> p)
{
  NodeType sum = 0;

  do
  {
    sum += p->data;
    p = p->next;
  } while (p != this->head);

  return sum;
}

// Method Overload
template <class NodeType>
NodeType NumberCircularLinkedList<NodeType>::total()
{
  return this->total(this->head); // Set Head Node as p Node
}

// Method that Returns the Highest Number in Linked List
template <class NodeType>
NodeType NumberCircularLinkedList<NodeType>::max(DoublyNodePtr<NodeType> p)
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

// Method Overload
template <class NodeType>
NodeType NumberCircularLinkedList<NodeType>::max()
{
  return this->max(this->head); // Set Head Node as p Node
}

// Method that Checks if the Given Number is Inside Linked List
template <class NodeType>
DoublyNodePtr<NodeType> NumberCircularLinkedList<NodeType>::linearSearch(DoublyNodePtr<NodeType> p, NodeType key)
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
template <class NodeType>
DoublyNodePtr<NodeType> NumberCircularLinkedList<NodeType>::linearSearch(NodeType key)
{
  return this->linearSearch(this->head, key); // Set Head Node as p Node
}

// Method to Compare Two Nodes Values
template <class NodeType>
int NumberCircularLinkedList<NodeType>::compare(int index1, int index2)
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