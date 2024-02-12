#include <cstdlib>
#include <math.h>

#include "../nodes/doublyNode.h"

using std::abs;

#ifndef DOUBLY_LINKED_LISTS
#define DOUBLY_LINKED_LISTS

// DoublyNodePtr Definition
template <class T>
using DoublyNodePtr = DoublyNode<T> *;

// DOUBLY LINKED LIST CLASS

template <class T>
class DoublyLinkedList
{
protected:
  DoublyNodePtr<T> head;
  DoublyNodePtr<T> tail;

  int length = 0;
  T error;

  // Private Methods
  void increaseLength();
  void increaseLength(int);
  void decreaseLength();
  DoublyNodePtr<T> move(int);
  T remove(bool);
  T pop(bool);
  T setNULL(bool);

public:
  // Constructors
  DoublyLinkedList(T);
  DoublyLinkedList(T, T);
  DoublyLinkedList(T[], int, T);
  ~DoublyLinkedList();

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
  int getLength();
  void concat(DoublyLinkedList);
};

// Doubly Linked List Constructors

// Create Doubly Linked List and Set Error Value
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(T error)
{
  // Default Error Value
  this->error = error;
}

// Add Head with Only One Next Node
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(T data, T error)
{
  DoublyNodePtr<T> p;

  // Default Error Value
  this->error = error;

  // Create New Node
  p = new DoublyNode<T>(data);

  // Set Node as Head and as Tail
  this->tail = this->head = p;

  // Increase Length
  this->increaseLength();
}

// Add Head and Multiple Next Nodes
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(T data[], int length, T error)
{
  DoublyNodePtr<T> p;

  // Default Error Value
  this->error = error;

  // Create First Node
  p = new DoublyNode<T>(data[0]);

  // Set p Node as Head
  this->head = p;

  // Add Next Nodes
  for (int i = 1; i < length; i++)
    // Add Node
    p = new DoublyNode<T>(data[i], p);

  // Set p Node as Tail
  this->tail = p;

  // Increase Length
  this->increaseLength(length);
}

// Destructor
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
  // Remove Tail Node if Linked List isn't Empty
  while (!isEmpty())
    this->pop(true);
}

// Method to Move to Next Node N Times
template <class T>
DoublyNodePtr<T> DoublyLinkedList<T>::move(int n)
{
  DoublyNodePtr<T> p;
  int mov = n > 0 ? n : n + 1;
  bool backwards = n < 0;

  // Works only for Negative n Values
  if (backwards)
    if (abs(mov) < this->length / 2)
      mov = abs(mov); // Get Absolute Value of mov
    else
    {
      backwards = false;
      mov = this->length + mov;
    }
  // Works only for Positive n Values
  else if (mov > this->length / 2)
  {
    backwards = true;
    mov = this->length - mov - 1;
  }

  // Move from Tail to Head, or from Head to Tail
  p = backwards ? this->tail : this->head;

  if (backwards)
    // Move to Previous N Nodes
    for (int i = 0; i < mov; i++)
    {
      // Check if Previous Node is NULL
      if (p->prev == NULL)
        return NULL;

      p = p->prev;
    }
  else
    // Move to Next N Nodes
    for (int i = 0; i < mov; i++)
    {
      // Check if Next Node is NULL
      if (p->next == NULL)
        return NULL;

      p = p->next;
    }
  return p;
}

// Method to Insert Node Before Head
template <class T>
void DoublyLinkedList<T>::push(T data)
{
  // Insert Node Before Head
  DoublyNodePtr<T> h = new DoublyNode<T>(data, NULL, this->head);

  // Set h Node as Head
  this->head = h;

  this->increaseLength();
}

// Method to Insert Node at Given Position
template <class T>
void DoublyLinkedList<T>::insertAt(T data, int pos)
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

  if (pos > 0)
    pos -= 1;

  DoublyNodePtr<T> p, n;

  // Move to Next or Prev Node pos Times
  p = this->move(pos);

  // pos is Out of Range
  if (p == NULL)
    return;

  // Get Next Node
  n = p->next;

  // Create New Node
  new DoublyNode<T>(data, p, n);

  this->increaseLength();
}

// Method to Insert Node at Tail
template <class T>
void DoublyLinkedList<T>::pushBack(T data)
{
  // Create New Node and Assign Old Tail as Previous Node
  DoublyNodePtr<T> n = new DoublyNode<T>(data, this->tail);

  // Set Tail
  this->tail = n;

  this->increaseLength();
}

// Method to Safely Remove Node that is Both Head and Tail
template <class T>
T DoublyLinkedList<T>::setNULL(bool destructor)
{
  DoublyNodePtr<T> t;

  // Get Tail
  t = this->tail;

  // Get Tail Data
  T data = t->data;

  // Set Head and Tail Node as NULL
  this->head = this->tail = NULL;

  // Deallocate Memory
  if (destructor)
    delete[] t;
  else
    delete t;

  return data;
}

// Method to Remove Head Node
template <class T>
T DoublyLinkedList<T>::remove(bool destructor)
{
  if (this->isEmpty())
    return this->error;

  // Head and Tail Node are the Same
  if (this->getLength() == 1)
    return this->setNULL(destructor);

  DoublyNodePtr<T> m, n;

  // Get Head Node
  m = this->head;
  T data = m->data;

  // Get Next Node to the One that will be Removed
  n = m->next;

  // Remove m Node from Linked List
  this->head = n;
  n->prev = NULL;

  // Deallocate Memory
  if (destructor)
    delete[] m;
  else
    delete m;

  decreaseLength();

  return data;
}

// Method Overloads
template <class T>
T DoublyLinkedList<T>::remove()
{
  return this->remove(false);
}

// Method to Remove Node at Tail
template <class T>
T DoublyLinkedList<T>::pop(bool destructor)
{
  if (this->isEmpty())
    return this->error;

  // Head and Tail Node are the Same
  if (this->getLength() == 1)
    return this->setNULL(destructor);

  DoublyNodePtr<T> t, p;

  this->decreaseLength();

  // Get Tail
  t = this->tail;

  // Get Tail Data
  T data = t->data;

  // Get Tail Previous Node
  p = this->tail->prev;

  // Remove Tail Node
  p->next = NULL;

  // Set Previous Node as Tail
  this->tail = p;

  // Deallocate Memory
  if (destructor)
    delete[] t;
  else
    delete t;

  return data;
}

// Method Overloads
template <class T>
T DoublyLinkedList<T>::pop()
{
  return this->pop(false);
}

// Method to Remove Node at Given Index
template <class T>
T DoublyLinkedList<T>::removeAt(int pos)
{
  // Check pos
  if (pos == -1 || pos >= this->length)
    return this->error; // Node not Found

  if (pos == 0)
    return this->remove(); // Remove Node at Head

  if (pos == this->length - 1)
    return this->pop(); // Remove Tail

  pos -= 1;

  DoublyNodePtr<T> p, m, n;

  this->decreaseLength();

  // Move to Next Node pos Times
  p = this->move(pos);

  // pos is Out of Range
  if (p == NULL)
    return this->error;

  // Get Node to Remove
  m = p->next;

  // Remove Node
  n = m->next;
  T data = m->data;
  p->next = n;
  n->prev = p;

  // Deallocate Memory
  delete m;

  return data;
}

// Method to Modify Node Value at Given Position
template <class T>
T DoublyLinkedList<T>::change(T data, int pos)
{
  if (this->isEmpty() || pos >= this->length)
    return this->error; // Node not Found

  // Move to Node
  DoublyNodePtr<T> m = this->move(pos);

  // pos is Out of Range
  if (m == NULL)
    return this->error;

  // Get Old Value
  T old = m->data;

  // Assign New Value
  m->data = data;

  return old;
}

// Method to Get Node at Given Position
template <class T>
T DoublyLinkedList<T>::get(int pos)
{
  // Check pos
  if (this->isEmpty() || pos >= this->length)
    return this->error; // Node not Found

  if (pos == 0)
    return this->head->data; // Get Node Next to Head

  if (pos == this->length - 1)
    return this->tail->data; // Get Tail

  // Move to Node
  DoublyNodePtr<T> m = this->move(pos);

  // pos is Out of Range
  if (m == NULL)
    return this->error;

  // Return Value
  return m->data;
}

// Method to Check if Linked List is Empty
template <class T>
bool DoublyLinkedList<T>::isEmpty()
{
  return this->head == NULL;
}

// Method to Increase Linked List Length
template <class T>
void DoublyLinkedList<T>::increaseLength()
{
  this->length += 1;
}

template <class T>
void DoublyLinkedList<T>::increaseLength(int length)
{
  this->length += length;
}

// Method to Decrease Linked List Length
template <class T>
void DoublyLinkedList<T>::decreaseLength()
{
  this->length -= 1;
}

// Method to Get Linked List Length
template <class T>
int DoublyLinkedList<T>::getLength()
{
  return this->length;
}

// Method to Concat Two Linked Lists
template <class T>
void DoublyLinkedList<T>::concat(DoublyLinkedList<T> l)
{
  // Assign l First Node Next to this Linked List Tail
  this->tail->next = l->head;
  l->head->prev = this->tail;

  // Save New Tail Node
  this->tail = l->tail;

  // Save New Length
  this->increaseLength(l->getLength());
}

#endif