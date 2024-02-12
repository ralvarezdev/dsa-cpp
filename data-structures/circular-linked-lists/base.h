#include <cstdlib>
#include <math.h>

#include "../doubly-linked-lists/base.h"

using std::abs;

#ifndef CIRCULAR_LINKED_LISTS
#define CIRCULAR_LINKED_LISTS

// CIRCULAR LINKED LIST CLASS

template <class T>
class CircularLinkedList
{
protected:
  DoublyNodePtr<T> head;

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
  CircularLinkedList(T);
  CircularLinkedList(T, T);
  CircularLinkedList(T[], int, T);
  ~CircularLinkedList();

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
  void concat(CircularLinkedList);
};

// Circular Linked List Constructors

// Create Circular Linked List and Set Error Value
template <class T>
CircularLinkedList<T>::CircularLinkedList(T error)
{
  // Default Error Value
  this->error = error;
}

// Add Head with Only One Next Node
template <class T>
CircularLinkedList<T>::CircularLinkedList(T data, T error)
{
  DoublyNodePtr<T> p;

  // Default Error Value
  this->error = error;

  // Create New Node
  p = new DoublyNode<T>(data);

  // Set Node as Head
  this->head = p;

  // Set Head as Head Next Node and as Head Previous Node
  this->head->next = this->head->prev = this->head;

  // Increase Length
  this->increaseLength();
}

// Add Head and Multiple Next Nodes
template <class T>
CircularLinkedList<T>::CircularLinkedList(T data[], int length, T error)
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

  // Set p Next Node to Head, and Set Head Previous Node to p
  p->next = this->head;
  this->head->prev = p;

  // Increase Length
  this->increaseLength(length);
}

// Destructor
template <class T>
CircularLinkedList<T>::~CircularLinkedList()
{
  // Remove Head Previous Node if It isn't Empty
  while (!isEmpty())
    this->pop(true);
}

// Method to Move to Next Node N Times
template <class T>
DoublyNodePtr<T> CircularLinkedList<T>::move(int n)
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

  // Move from Head Previous Node to Head, or from Head to Head Previous Node
  p = backwards ? this->head->prev : this->head;

  if (backwards)
    // Move to Previous N Nodes
    for (int i = 0; i < mov; i++)
      p = p->prev;
  else
    // Move to Next N Nodes
    for (int i = 0; i < mov; i++)
      p = p->next;
  return p;
}

// Method to Insert Node Before Head
template <class T>
void CircularLinkedList<T>::push(T data)
{
  DoublyNodePtr<T> h;

  // Insert Node Before Head
  if (this->isEmpty())
  {
    h = new DoublyNode<T>(data, NULL, NULL);
    h->prev = h->next = h;
  }
  else
    h = new DoublyNode<T>(data, this->head->prev, this->head);

  // Set h Node as Head
  this->head = h;

  this->increaseLength();
}

// Method to Insert Node at Given Position
template <class T>
void CircularLinkedList<T>::insertAt(T data, int pos)
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

  // Get Next Node
  n = p->next;

  // Create New Node
  new DoublyNode<T>(data, p, n);

  this->increaseLength();
}

// Method to Insert Node at Head Previous Node
template <class T>
void CircularLinkedList<T>::pushBack(T data)
{
  // Create New Node and Assign Old Head Previous Node as Previous Node
  DoublyNodePtr<T> n = new DoublyNode<T>(data, this->head->prev, this->head);

  this->increaseLength();
}

// Method to Safely Remove Head Node when it's the Only Node in Linked List
template <class T>
T CircularLinkedList<T>::setNULL(bool destructor)
{
  DoublyNodePtr<T> h;

  // Get Head Node
  h = this->head;

  // Get Head Data
  T data = h->data;

  // Set Head as NULL
  this->head = NULL;

  // Deallocate Memory
  if (destructor)
    delete[] h;
  else
    delete h;

  return data;
}

// Method to Remove Head Node
template <class T>
T CircularLinkedList<T>::remove(bool destructor)
{
  DoublyNodePtr<T> m, n;

  if (this->isEmpty())
    return this->error;

  // Linked List Only have One Node which is Head
  if (this->getLength() == 1)
    return this->setNULL(destructor);

  // Get Head Node
  m = this->head;
  T data = m->data;

  // Get Next Node to the One that will be Removed
  n = m->next;

  // Remove m Node from Linked List
  n->prev = this->head->prev;
  this->head->prev->next = n;
  this->head = n;

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
T CircularLinkedList<T>::remove()
{
  return this->remove(false);
}

// Method to Remove Node at Head Previous Node
template <class T>
T CircularLinkedList<T>::pop(bool destructor)
{
  if (this->isEmpty())
    return this->error;

  // Linked List Only have One Node which is Head
  if (this->getLength() == 1)
    return this->setNULL(destructor);

  DoublyNodePtr<T> t, p;

  this->decreaseLength();

  // Set Head Previous Node as Tail;
  t = this->head->prev;

  // Get Tail Previous Node
  p = t->prev;

  // Get Tail Data
  T data = t->data;

  // Set Tail Next Node to Head
  p->next = this->head;

  // Set Head Previous Node to Tail Previous Node
  this->head->prev = p;

  // Deallocate Memory
  if (destructor)
    delete[] t;
  else
    delete t;

  return data;
}

// Method Overloads
template <class T>
T CircularLinkedList<T>::pop()
{
  return this->pop(false);
}

// Method to Remove Node at Given Index
template <class T>
T CircularLinkedList<T>::removeAt(int pos)
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
T CircularLinkedList<T>::change(T data, int pos)
{
  if (this->isEmpty() || pos >= this->length)
    return this->error; // Node not Found

  // Move to Node
  DoublyNodePtr<T> m = this->move(pos);

  // Get Old Value
  T old = m->data;

  // Assign New Value
  m->data = data;

  return old;
}

// Method to Get Node at Given Position
template <class T>
T CircularLinkedList<T>::get(int pos)
{
  // Check pos
  if (this->isEmpty() || pos >= this->length)
    return this->error; // Node not Found

  if (pos == 0)
    return this->head->data; // Get Node Next to Head Data

  if (pos == this->length - 1)
    return this->head->prev->data; // Get Head Previous Node Data

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
bool CircularLinkedList<T>::isEmpty()
{
  return this->head == NULL;
}

// Method to Increase Linked List Length
template <class T>
void CircularLinkedList<T>::increaseLength()
{
  this->length += 1;
}

template <class T>
void CircularLinkedList<T>::increaseLength(int length)
{
  this->length += length;
}

// Method to Decrease Linked List Length
template <class T>
void CircularLinkedList<T>::decreaseLength()
{
  this->length -= 1;
}

// Method to Get Linked List Length
template <class T>
int CircularLinkedList<T>::getLength()
{
  return this->length;
}

// Method to Concat Two Linked Lists
template <class T>
void CircularLinkedList<T>::concat(CircularLinkedList<T> l)
{
  // Assign l First Node Next to this Linked List Head Previous Node
  this->head->prev->next = l->head;
  l->head->prev = this->head->prev;

  // Save New Head Previous Node
  this->head->prev = l->head->prev;

  // Save New Length
  this->increaseLength(l->getLength());
}

#endif