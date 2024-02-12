#include <cstdlib>

#include "../nodes/singleNode.h"

#ifndef SINGLE_LINKED_LISTS
#define SINGLE_LINKED_LISTS

// SingleNodePtr Definition
template <class T>
using SingleNodePtr = SingleNode<T> *;

// SINGLE LINKED LIST CLASS

template <class T>
class SingleLinkedList
{
protected:
  SingleNodePtr<T> head;
  SingleNodePtr<T> tail;
  // SingleNodePtr<T> curr;

  int length = 0;
  T error;

  // Private Methods
  void increaseLength();
  void increaseLength(int);
  void decreaseLength();
  SingleNodePtr<T> move(SingleNodePtr<T>, int);
  T remove(bool);

public:
  // Constructors
  SingleLinkedList(T);
  SingleLinkedList(T, T);
  SingleLinkedList(T[], int, T);
  ~SingleLinkedList();

  // Public Methods
  bool isEmpty();
  void push(T);
  void pushBack(T);
  void insertAt(T, int);
  T remove();
  T pop();
  T removeAt(int);
  T change(T, int);
  T get(int);
  // void setCurrent(SingleNodePtr<T>);
  // void setCurrent();
  //  int count(SingleNodePtr<T>);
  int getLength();
  void concat(SingleLinkedList);
};

// Single Linked List Constructors

// Add Head with Next Node as NULL
template <class T>
SingleLinkedList<T>::SingleLinkedList(T error)
{
  SingleNodePtr<T> p;

  // Default Error Value
  this->error = error;

  // Add Node as Head and Tail
  this->head = this->tail = p = new SingleNode<T>();

  /*
    // Set Head as Current Node
    this->setCurrent();
  */
}

// Add Head with Only One Next Node
template <class T>
SingleLinkedList<T>::SingleLinkedList(T data, T error)
{
  SingleNodePtr<T> p;

  // Default Error Value
  this->error = error;

  // Add Head
  this->head = p = new SingleNode<T>();

  // Add Next Node
  p = new SingleNode<T>(data);

  // Add Node as Head Next Node and as Tail
  this->tail = this->head->next = p;

  // Increase Length
  this->increaseLength();

  /*
    // Set Head as Current Node
    this->setCurrent();
  */
}

// Add Head and Multiple Next Nodes
template <class T>
SingleLinkedList<T>::SingleLinkedList(T data[], int length, T error)
{
  SingleNodePtr<T> p;

  // Default Error Value
  this->error = error;

  // Add Head
  this->head = p = new SingleNode<T>();

  // Add Next Nodes
  for (int i = 0; i < length; i++)
  {
    // Add Node
    p->next = new SingleNode<T>(data[i]);

    // Move to Next Node
    p = p->next;
  }

  // Set p Node as Tail
  this->tail = p;

  // Increase Length
  this->increaseLength(length);

  /*
    // Set Head as Current Node
    this->setCurrent();
  */
}

// Destructor
template <class T>
SingleLinkedList<T>::~SingleLinkedList()
{
  // Remove Node Next to Head if It isn't Empty
  while (!isEmpty())
    this->remove(true);

  // Remove Head Node
  SingleNodePtr<T> temp = this->head;
  this->head = NULL;

  delete[] temp;
}

// Method to Move to Next Node N Times
template <class T>
SingleNodePtr<T> SingleLinkedList<T>::move(SingleNodePtr<T> p, int n)
{
  // Move to Next N Nodes
  for (int i = 0; i < n; i++)
  {
    // Check if Next Node is NULL
    if (p->next == NULL)
      return NULL;

    p = p->next;
  }
  return p;
}

// Method to Insert Node Next to Head
template <class T>
void SingleLinkedList<T>::push(T data)
{
  SingleNodePtr<T> n, p;

  // Insert Node Next to Head
  n = this->head->next;
  p = new SingleNode<T>(data, n);

  // Set Node as Tail
  if (this->getLength() == 0)
    this->tail = p;

  // Set Node Next to Head
  this->head->next = p;

  this->increaseLength();
}

// Method to Insert Node at Given Position
template <class T>
void SingleLinkedList<T>::insertAt(T data, int pos)
{
  // Check pos
  if (pos == 0)
  {
    this->push(data); // Insert Node Next to Head
    return;
  }

  if (pos == -1 || pos >= this->length)
  {
    this->pushBack(data); // Insert Node at Tail
    return;
  }

  if (pos < 0)
    pos = this->length + pos + 1; // Get Position

  SingleNodePtr<T> p, m, n;

  // Move to Next Node pos Times
  p = this->move(this->head, pos);

  // pos is Out of Range
  if (p == NULL)
    return;

  // Get Next Node
  n = p->next;

  // Create New Node and Set m as Next Node
  m = new SingleNode<T>(data, n);

  // Set Node at Given Position
  p->next = m;

  this->increaseLength();
}

// Method to Insert Node at Tail
template <class T>
void SingleLinkedList<T>::pushBack(T data)
{
  SingleNodePtr<T> n = new SingleNode<T>(data);

  // Set Node at Tail
  this->tail->next = n;

  // Set Tail
  this->tail = n;

  this->increaseLength();
}

// Method to Remove Node Next to Head
template <class T>
T SingleLinkedList<T>::remove(bool destructor)
{
  if (this->isEmpty())
    return this->error;

  // Get Node Next to Head
  SingleNodePtr<T> n = this->head->next;
  T data = n->data;

  // Remove n Node from Linked List
  head->next = n->next;

  // Deallocate Memory
  if (destructor)
    delete[] n;
  else
    delete n;

  decreaseLength();

  return data;
}

// Method Overloads
template <class T>
T SingleLinkedList<T>::remove()
{
  return this->remove(false);
}

// Method to Remove Node at Tail
template <class T>
T SingleLinkedList<T>::pop()
{
  if (this->isEmpty())
    return this->error;

  SingleNodePtr<T> t, p;

  this->decreaseLength();

  // Move to Tail Previous Node
  p = this->move(this->head, this->length);

  // Get Tail
  t = this->tail;
  T data = t->data;
  p->next = NULL;

  // Set Previous Node as Tail
  this->tail = p;

  // Deallocate Memory
  delete t;

  return data;
}

// Method to Remove Node at Given Index
template <class T>
T SingleLinkedList<T>::removeAt(int pos)
{
  // Check pos
  if (pos == 0)
    return this->remove(); // Remove Node Next to Head

  if (pos < 0)
    pos = this->length + pos; // Get Position

  if (pos > this->length)
    return this->error; // Node not Found

  if (pos == -1 || pos == this->length)
    return this->pop(); // Remove Tail

  SingleNodePtr<T> p, m, n;

  this->decreaseLength();

  // Move to Next Node pos Times
  p = this->move(this->head, pos);

  // pos is Out of Range
  if (p == NULL)
    return this->error;

  // Get Node to Remove
  m = p->next;

  // Remove Node
  n = m->next;
  T data = m->data;
  p->next = n;

  // Deallocate Memory
  delete m;

  return data;
}

// Method to Modify Node Value at Given Position
template <class T>
T SingleLinkedList<T>::change(T data, int pos)
{
  SingleNodePtr<T> n;
  T old;

  if (pos == 0)
  {
    old = this->head->next->data;
    this->head->next->data = data; // Change Value to Node Next to Head
    return old;
  }

  if (pos < 0)
    pos = this->length + pos; // Get Position
  pos += 1;

  if (pos > this->length)
    return this->error; // Node not Found

  if (pos == this->length)
  {
    old = this->tail->data;
    this->tail->data = data; // Change Value to Tail
    return old;
  }

  if (this->isEmpty())
    return this->error;

  // Set Head to n
  n = this->head;

  // Move to Node
  n = this->move(n, pos);

  // pos is Out of Range
  if (n == NULL)
    return this->error;

  // Assign New Value
  old = n->data;
  n->data = data;

  return old;
}

// Method to Get Node at Given Position
template <class T>
T SingleLinkedList<T>::get(int pos)
{
  // Check pos
  if (this->isEmpty())
    return this->error;

  if (pos == 0)
    return this->head->next->data; // Get Node Next to Head

  if (pos == this->length)
    return this->tail->data; // Get Tail

  if (pos > this->length)
    return this->error; // Node not Found

  if (pos < 0)
    pos = this->length + pos; // Get Position
  pos += 1;

  SingleNodePtr<T> n;

  n = this->head;

  // Move to Node
  n = this->move(n, pos);

  // pos is Out of Range
  if (n == NULL)
    return this->error;

  // Return Value
  return n->data;
}

// Method to Check if Linked List is Empty
template <class T>
bool SingleLinkedList<T>::isEmpty()
{
  return this->head->next == NULL;
}

// Method to Increase Linked List Length
template <class T>
void SingleLinkedList<T>::increaseLength()
{
  this->length += 1;
}

template <class T>
void SingleLinkedList<T>::increaseLength(int length)
{
  this->length += length;
}

// Method to Decrease Linked List Length
template <class T>
void SingleLinkedList<T>::decreaseLength()
{
  this->length -= 1;
}

/*
// Method to Set Current Node
template <class T>
void SingleLinkedList<T>::setCurrent(SingleNodePtr<T> p)
{
  this->curr = p;
}

// Method Overload to Set Head Node as Current Node
template <class T>
void SingleLinkedList<T>::setCurrent()
{
  this->curr = this->head;
}
*/

/*
// Count Nodes with a Recursive Method
template <class T>
int SingleLinkedList<T>::count(SingleNodePtr<T> p)
{
  if (p != NULL)
    return count(p->next) + 1;

  // Set Head Node as Current Node
  this->setCurrent();

  return 0;
}
*/

// Method to Get Linked List Length
template <class T>
int SingleLinkedList<T>::getLength()
{
  return this->length;
}

// Method to Concat Two Linked Lists
template <class T>
void SingleLinkedList<T>::concat(SingleLinkedList<T> l)
{
  // Assign l First Node Next to this Linked List Tail
  this->tail->next = l->head->next;

  // Save New Tail Node
  this->tail = l->tail;

  // Save New Length
  this->increaseLength(l->getLength());
}

#endif