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

#ifndef NUMBER_CIRCULAR_SINGLE_LINKED_LISTS
#define NUMBER_CIRCULAR_SINGLE_LINKED_LISTS

// NUMBER SINGLE LINKED LIST NAMESPACE
namespace numberCSLL
{
  const int nIndex = 6;
  const int nDigits = 10;
}

// NUMBER CIRCULAR SINGLE LINKED LIST CLASS

template <class NodeType>
class NumberCircularSingleLinkedList : public CircularSingleLinkedList<NodeType>
{
protected:
  // Protected Methods
  void print(SingleNodePtr<NodeType>);
  void printReverse(SingleNodePtr<NodeType>);
  NodeType total(SingleNodePtr<NodeType>);
  NodeType max(SingleNodePtr<NodeType>);
  bool linearSearch(SingleNodePtr<NodeType>, NodeType);

public:
  // Inherit Constructors
  using CircularSingleLinkedList<NodeType>::CircularSingleLinkedList;

  // Constructors
  NumberCircularSingleLinkedList() : CircularSingleLinkedList<NodeType>(-1){};

  // Public Methods
  void print() { print(this->head); }                                        // Set Head Node as p Node
  void printReverse() { printReverse(this->head); };                         // ...
  NodeType total() { return total(this->head); };                            // ...
  NodeType max() { return max(this->head); };                                // ...
  bool linearSearch(NodeType key) { return linearSearch(this->head, key); }; // ...

  int compare(int, int);
};

// Method to Print Nodes from Head to Tail
template <class NodeType>
void NumberCircularSingleLinkedList<NodeType>::print(SingleNodePtr<NodeType> p)
{
  int n = 0;

  // Prints Header
  cout << left << setw(numberCSLL::nIndex) << setfill(' ') << "Index"
       << setw(numberCSLL::nDigits + 1) << setfill(' ') << "Node"
       << '\n';

  // Prints from Head to Tail
  do
  {
    cout << setw(numberCSLL::nIndex) << setfill(' ') << n++
         << setw(numberCSLL::nDigits + 1) << setfill(' ') << p->data
         << '\n';
    p = p->next;
  } while (p != this->head);
}

// Print Nodes with a Recursive Method from Tail to Head
template <class NodeType>
void NumberCircularSingleLinkedList<NodeType>::printReverse(SingleNodePtr<NodeType> p)
{
  static int iter = 0;
  static int n = this->length - 1;

  // Prints from Tail to Head
  // NOTE: If the Print Statement is before the Recursive Function Call, Nodes will be Printed from Head to Tail
  if (iter == 0 || p != this->head) // Same Expression as !p or p==0
  {
    iter++;
    this->printReverse(p->next);

    cout << setw(numberCSLL::nIndex) << setfill(' ') << n--
         << setw(numberCSLL::nDigits + 1) << setfill(' ') << p->data
         << '\n';

    return;
  }

  // Prints Header
  cout << left << setw(numberCSLL::nIndex) << setfill(' ') << "Index"
       << setw(numberCSLL::nDigits + 1) << setfill(' ') << "Node"
       << '\n';

  iter == 0;
}

// Method that Returns the Sum of All Node's Data Field
template <class NodeType>
NodeType NumberCircularSingleLinkedList<NodeType>::total(SingleNodePtr<NodeType> p)
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
NodeType NumberCircularSingleLinkedList<NodeType>::max(SingleNodePtr<NodeType> p)
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
bool NumberCircularSingleLinkedList<NodeType>::linearSearch(SingleNodePtr<NodeType> p, NodeType key)
{
  do
  {
    if (key == p->data)
      return true;

    p = p->next;
  } while (p != this->head);

  return false;
}

// Method to Compare Two Nodes Values
template <class NodeType>
int NumberCircularSingleLinkedList<NodeType>::compare(int index1, int index2)
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

  if (index1 == index2)
    return 0;

  return index1 > index2 ? 1 : 2;
}

#endif