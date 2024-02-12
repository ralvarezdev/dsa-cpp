#include <cstdlib>

#ifndef STACK_LINKED_LISTS
#define STACK_LINKED_LISTS

// NODE CLASS
// Self-Referential Structure

template <class T>
class StackNode
{
public:
  T data;
  StackNode *next = NULL;

  // Constructors
  StackNode();
  StackNode(T);
  StackNode(T, StackNode *);
};

// StackNodePtr Definition
template <class T>
using StackNodePtr = StackNode<T> *;

// STACK LINKED LIST CLASS
// LIFO
// Last-in, First-out

template <class T>
class StackLinkedList
{
protected:
  StackNodePtr<T> head;

  int length = 0;
  T error;

  // Private Methods
  void increaseLength();
  void increaseLength(int);
  void decreaseLength();

public:
  // Constructors
  StackLinkedList(T, T);
  StackLinkedList(T[], int, T);
  ~StackLinkedList();

  // Public Methods
  bool isEmpty();
  void push(T);
  T pop(bool);
  T pop();
  T top();
  int getLength();
};

// Node Class Constructors
template <class T>
StackNode<T>::StackNode()
{
  return;
}

template <class T>
StackNode<T>::StackNode(T data)
{
  this->data = data;
}

template <class T>
StackNode<T>::StackNode(T data, StackNode<T> *next)
{
  this->data = data;
  this->next = next;
}

// STACK LINKED LIST CLASS

// Stack Constructors

// Add Head with Only One Next Node
template <class T>
StackLinkedList<T>::StackLinkedList(T data, T error)
{
  StackNodePtr<T> p;

  // Default Error Value
  this->error = error;

  // Create New Node
  p = new StackNode<T>(data);

  // Set Node as Head
  this->head = p;

  // Increase Length
  this->increaseLength();
}

// Add Head and Multiple Next Nodes
template <class T>
StackLinkedList<T>::StackLinkedList(T data[], int length, T error)
{
  // Default Error Value
  this->error = error;

  // Create First Node
  this->head = new StackNode<T>(data[0]);

  // Add Next Nodes
  for (int i = 1; i < length; i++)
    // Add Node
    this->head = new StackNode<T>(data[i], this->head);

  // Increase Length
  this->increaseLength(length);
}

// Destructor
template <class T>
StackLinkedList<T>::~StackLinkedList()
{
  // Remove Node Next to Head if It isn't Empty
  while (!isEmpty())
    this->pop(true);

  // Remove Head Node
  StackNodePtr<T> temp = this->head;
  this->head = NULL;

  delete[] temp;
}

// Method to Insert Node Before Head
template <class T>
void StackLinkedList<T>::push(T data)
{
  // Insert Node Before Head
  StackNodePtr<T> h = new StackNode<T>(data, this->head);

  // Set h Node as Head
  this->head = h;

  this->increaseLength();
}

// Method to Remove Head Node
template <class T>
T StackLinkedList<T>::pop(bool destructor)
{
  StackNodePtr<T> m, n;

  if (this->isEmpty())
    return this->error;

  // Get Head Node
  m = this->head;
  T data = m->data;

  // Get Next Node to the One that will be Removed
  n = m->next;

  // Remove m Node from Stack
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
T StackLinkedList<T>::pop()
{
  return this->pop(false);
}

// Method to Get Node Data at Top Position
template <class T>
T StackLinkedList<T>::top()
{
  // Check pos
  if (this->isEmpty())
    return this->error;

  return this->head->data;
}

// Method to Check if Stack is Empty
template <class T>
bool StackLinkedList<T>::isEmpty()
{
  return this->head == NULL;
}

// Method to Increase Stack Length
template <class T>
void StackLinkedList<T>::increaseLength()
{
  this->length += 1;
}

template <class T>
void StackLinkedList<T>::increaseLength(int length)
{
  this->length += length;
}

// Method to Decrease Stack Length
template <class T>
void StackLinkedList<T>::decreaseLength()
{
  this->length -= 1;
}

// Method to Get Stack Length
template <class T>
int StackLinkedList<T>::getLength()
{
  return this->length;
}

#endif