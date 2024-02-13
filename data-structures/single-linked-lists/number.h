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

#ifndef NUMBER_SINGLE_LINKED_LISTS
#define NUMBER_SINGLE_LINKED_LISTS

// NUMBER LINKED LIST CLASS

template <class NodeType>
class NumberSingleLinkedList : public SingleLinkedList<NodeType>
{
public:
  // Inherit Constructors
  using SingleLinkedList<NodeType>::SingleLinkedList;

  // Public Methods
  void insertionSort(NodeType);
  void print();
  void print(SingleNodePtr<NodeType>);
  void printReverse();
  void printReverse(SingleNodePtr<NodeType>);
  NodeType total();
  NodeType total(SingleNodePtr<NodeType>);
  NodeType max();
  NodeType max(SingleNodePtr<NodeType>);
  SingleNodePtr<NodeType> linearSearch(NodeType);
  SingleNodePtr<NodeType> linearSearch(SingleNodePtr<NodeType>, NodeType);
  int compare(int, int);
};

// Method to Insert Node by Insertion Sort
template <class NodeType>
void NumberSingleLinkedList<NodeType>::insertionSort(NodeType data)
{
  SingleNodePtr<NodeType> p, m, n;

  // Insert Node Next to Head
  if (this->getLength() == 0)
  {
    this->push(data);
    return;
  }

  int pos = 0;
  n = this->head->next;
  p = this->head;

  while (n != NULL)
  {
    if (n->data > data)
    {
      // Insert Node at pos Index
      this->insertAt(data, pos);
      return;
    }

    p = n;
    n = n->next;
    pos++;
  }

  // Insert Node at Tail
  this->pushBack(data);
}

// Method Print Nodes from Head to Tail
template <class NodeType>
void NumberSingleLinkedList<NodeType>::print(SingleNodePtr<NodeType> p)
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
void NumberSingleLinkedList<NodeType>::print()
{
  this->print(this->head->next); // Set Head Node as p Node
}

// Print Nodes with a Recursive Method from Tail to Head
template <class NodeType>
void NumberSingleLinkedList<NodeType>::printReverse(SingleNodePtr<NodeType> p)
{
  static int n = this->length - 1;

  // Prints from Tail to Head
  // NOTE: If the Print Statement is before the Recursive Function Call, Nodes will be Printed from Head to Tail

  if (p != NULL) // Same Expression as !p or p==0
  {
    this->printReverse(p->next);
    cout << setw(6) << n-- << p->data << '\n';

    return;
  }
  cout << setw(6) << left << setfill(' ') << "Index" << setw(10) << "Node" << '\n';
}

// Method Overload
template <class NodeType>
void NumberSingleLinkedList<NodeType>::printReverse()
{
  this->printReverse(this->head->next); // Set Head Node as p Node
}

// Method that Returns the Sum of All Node's Data Field
template <class NodeType>
NodeType NumberSingleLinkedList<NodeType>::total(SingleNodePtr<NodeType> p)
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
NodeType NumberSingleLinkedList<NodeType>::total()
{
  return this->total(this->head->next); // Set Head Node as p Node
}

// Method that Returns the Highest Number in Linked List
template <class NodeType>
NodeType NumberSingleLinkedList<NodeType>::max(SingleNodePtr<NodeType> p)
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
NodeType NumberSingleLinkedList<NodeType>::max()
{
  return this->max(this->head->next); // Set Head Node as p Node
}

/*
// Recursive Method that Returns the Highest Number in Linked List
template <class NodeType>
NodeType NumberSingleLinkedList<NodeType>::max()
{
  static NodeType m = -1;
  SingleNodePtr p = this->curr;

  if (p == NULL)
  {
    // Set Head Node as Current Node
    SingleLinkedList<NodeType>::setCurrent();

    return -1;
  }

  this->curr = this->curr->next;
  m = this->max();

  return m > p->data ? m : p->data;
}
*/

// Method that Checks if the Given Number is Inside Linked List
template <class NodeType>
SingleNodePtr<NodeType> NumberSingleLinkedList<NodeType>::linearSearch(SingleNodePtr<NodeType> p, NodeType key)
{
  SingleNodePtr<NodeType> q;

  while (p != NULL)
  {
    if (key == p->data)
    {
      // Set p Node as Tail
      if (p->next == NULL)
        this->tail = q;

      // Move Node whose Key Matched Next to Head in Order to Improve Performance
      q->next = p->next;
      p->next = this->head->next;
      this->head->next = p;

      /*
        // Set Head Node as Current Node
        SingleLinkedList<NodeType>::setCurrent();
      */

      return p;
    }
    q = p;
    p = p->next;
  }

  /*
    // Set Head Node as Current Node
    SingleLinkedList<NodeType>::setCurrent();
  */

  return NULL;
}

// Method Overload
template <class NodeType>
SingleNodePtr<NodeType> NumberSingleLinkedList<NodeType>::linearSearch(NodeType key)
{
  return this->linearSearch(this->head->next, key); // Set Head Node as p Node
}

/*
// Recursive Method that Checks if the Given Number is Inside Linked List
template <class NodeType>
SingleNodePtr<NodeType> NumberSingleLinkedList<NodeType>::linearSearch(NodeType key)
{
  // Get Current Node
  SingleNodePtr<NodeType> p = this->curr;

  if (p == NULL)
  {
    // Set Head Node as Current Node
    SingleLinkedList<NodeType>::setCurrent();
    return NULL;
  }

  if (key == p->data)
    return p;

  this->curr = this->curr->next;
  return this->linearSearch(key);
}
*/

// Method to Compare Two Nodes Values
template <class NodeType>
int NumberSingleLinkedList<NodeType>::compare(int index1, int index2)
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