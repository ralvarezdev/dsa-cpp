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

template <class T>
class NumberSingleLinkedList : public SingleLinkedList<T>
{
public:
  // Inherit Constructors
  using SingleLinkedList<T>::SingleLinkedList;

  // Public Methods
  void insertionSort(T);
  void print();
  void print(SingleNodePtr<T>);
  void printReverse();
  void printReverse(SingleNodePtr<T>);
  T total();
  T total(SingleNodePtr<T>);
  T max();
  T max(SingleNodePtr<T>);
  SingleNodePtr<T> linearSearch(T);
  SingleNodePtr<T> linearSearch(SingleNodePtr<T>, T);
  int compare(int, int);
};

// Method to Insert Node by Insertion Sort
template <class T>
void NumberSingleLinkedList<T>::insertionSort(T data)
{
  SingleNodePtr<T> p, m, n;

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
template <class T>
void NumberSingleLinkedList<T>::print(SingleNodePtr<T> p)
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
void NumberSingleLinkedList<T>::print()
{
  this->print(this->head->next); // Set Head Node as p Node
}

// Print Nodes with a Recursive Method from Tail to Head
template <class T>
void NumberSingleLinkedList<T>::printReverse(SingleNodePtr<T> p)
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
template <class T>
void NumberSingleLinkedList<T>::printReverse()
{
  this->printReverse(this->head->next); // Set Head Node as p Node
}

// Method that Returns the Sum of All Node's Data Field
template <class T>
T NumberSingleLinkedList<T>::total(SingleNodePtr<T> p)
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
T NumberSingleLinkedList<T>::total()
{
  return this->total(this->head->next); // Set Head Node as p Node
}

// Method that Returns the Highest Number in Linked List
template <class T>
T NumberSingleLinkedList<T>::max(SingleNodePtr<T> p)
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
T NumberSingleLinkedList<T>::max()
{
  return this->max(this->head->next); // Set Head Node as p Node
}

/*
// Recursive Method that Returns the Highest Number in Linked List
template <class T>
T NumberSingleLinkedList<T>::max()
{
  static T m = -1;
  SingleNodePtr p = this->curr;

  if (p == NULL)
  {
    // Set Head Node as Current Node
    SingleLinkedList<T>::setCurrent();

    return -1;
  }

  this->curr = this->curr->next;
  m = this->max();

  return m > p->data ? m : p->data;
}
*/

// Method that Checks if the Given Number is Inside Linked List
template <class T>
SingleNodePtr<T> NumberSingleLinkedList<T>::linearSearch(SingleNodePtr<T> p, T key)
{
  SingleNodePtr<T> q;

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
        SingleLinkedList<T>::setCurrent();
      */

      return p;
    }
    q = p;
    p = p->next;
  }

  /*
    // Set Head Node as Current Node
    SingleLinkedList<T>::setCurrent();
  */

  return NULL;
}

// Method Overload
template <class T>
SingleNodePtr<T> NumberSingleLinkedList<T>::linearSearch(T key)
{
  return this->linearSearch(this->head->next, key); // Set Head Node as p Node
}

/*
// Recursive Method that Checks if the Given Number is Inside Linked List
template <class T>
SingleNodePtr<T> NumberSingleLinkedList<T>::linearSearch(T key)
{
  // Get Current Node
  SingleNodePtr<T> p = this->curr;

  if (p == NULL)
  {
    // Set Head Node as Current Node
    SingleLinkedList<T>::setCurrent();
    return NULL;
  }

  if (key == p->data)
    return p;

  this->curr = this->curr->next;
  return this->linearSearch(key);
}
*/

// Method to Compare Two Nodes Values
template <class T>
int NumberSingleLinkedList<T>::compare(int index1, int index2)
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