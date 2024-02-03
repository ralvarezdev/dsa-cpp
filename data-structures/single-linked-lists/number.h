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

#ifndef NUMBER_LINKED_LISTS
#define NUMBER_LINKED_LISTS

// NUMBER LINKED LIST CLASS

template <class T>
class NumberLinkedList : public SingleLinkedList<T>
{
public:
  // Inherit Constructors
  using SingleLinkedList<T>::SingleLinkedList;

  // Public Methods
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
};

// Print Nodes Method from Head to Tail
template <class T>
void NumberLinkedList<T>::print(SingleNodePtr<T> p)
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
void NumberLinkedList<T>::print()
{
  this->print(this->head->next); // Set Head Node as p Node
}

// Print Nodes with a Recursive Method from Tail to Head
template <class T>
void NumberLinkedList<T>::printReverse(SingleNodePtr<T> p)
{
  static int n = this->length;

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
void NumberLinkedList<T>::printReverse()
{
  this->printReverse(this->head->next); // Set Head Node as p Node
}

// Method that Returns the Sum of All Node's Data Field
template <class T>
T NumberLinkedList<T>::total(SingleNodePtr<T> p)
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
T NumberLinkedList<T>::total()
{
  return this->total(this->head->next); // Set Head Node as p Node
}

// Method that Returns the Highest Number in Linked List
template <class T>
T NumberLinkedList<T>::max(SingleNodePtr<T> p)
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
T NumberLinkedList<T>::max()
{
  return this->max(this->head->next); // Set Head Node as p Node
}

/*
// Recursive Method that Returns the Highest Number in Linked List
template <class T>
T NumberLinkedList<T>::max()
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
SingleNodePtr<T> NumberLinkedList<T>::linearSearch(SingleNodePtr<T> p, T key)
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
SingleNodePtr<T> NumberLinkedList<T>::linearSearch(T key)
{
  return this->linearSearch(this->head->next, key); // Set Head Node as p Node
}

/*
// Recursive Method that Checks if the Given Number is Inside Linked List
template <class T>
SingleNodePtr<T> NumberLinkedList<T>::linearSearch(T key)
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

#endif