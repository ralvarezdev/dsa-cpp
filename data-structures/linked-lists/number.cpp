#include <iostream>
#include <string>
#include <limits.h>
#include <cstdlib>
#include <iomanip>

#include "base.h"
#include "number.h"

using std::cout;
using std::left;
using std::setfill;
using std::setw;
using std::string;

// Explicit Template Initialization
template class NumberLinkedList<int>;

// template class Node<float>;
// template class LinkedList<float>;
// template class NumberLinkedList<float>;

// template class Node<double>;
// template class LinkedList<double>;
// template class NumberLinkedList<double>;

// Print Nodes Method from Head to Tail
template <class T>
void NumberLinkedList<T>::print(NodePtr<T> p)
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
void NumberLinkedList<T>::printReverse(NodePtr<T> p)
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
T NumberLinkedList<T>::total(NodePtr<T> p)
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
T NumberLinkedList<T>::max(NodePtr<T> p)
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
  NodePtr p = this->curr;

  if (p == NULL)
  {
    // Set Head Node as Current Node
    LinkedList<T>::setCurrent();

    return -1;
  }

  this->curr = this->curr->next;
  m = this->max();

  return m > p->data ? m : p->data;
}
*/

// Method that Checks if the Given Number is Inside Linked List
template <class T>
NodePtr<T> NumberLinkedList<T>::linearSearch(NodePtr<T> p, T key)
{
  NodePtr<T> q;

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

      // Set Head Node as Current Node
      LinkedList<T>::setCurrent();
      // this->template LinkedList<T>::setCurrent();
      // this->LinkedList<T>::setCurrent();
      return p;
    }
    q = p;
    p = p->next;
  }

  // Set Head Node as Current Node
  LinkedList<T>::setCurrent();
  // this->template LinkedList<T>::setCurrent();
  // this->LinkedList<T>::setCurrent();
  return NULL;
}

// Method Overload
template <class T>
NodePtr<T> NumberLinkedList<T>::linearSearch(T key)
{
  return this->linearSearch(this->head->next, key); // Set Head Node as p Node
}

/*
// Recursive Method that Checks if the Given Number is Inside Linked List
template <class T>
NodePtr<T> NumberLinkedList<T>::linearSearch(T key)
{
  // Get Current Node
  NodePtr<T> p = this->curr;

  if (p == NULL)
  {
    // Set Head Node as Current Node
    LinkedList<T>::setCurrent();
    return NULL;
  }

  if (key == p->data)
    return p;

  this->curr = this->curr->next;
  return this->linearSearch(key);
}
*/
