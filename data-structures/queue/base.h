#include <cstdlib>

#ifndef QUEUE_LINKED_LISTS
#define QUEUE_LINKED_LISTS

// NODE CLASS
// Self-Referential Structure

template <class T>
class SingleNode
{
public:
  T data;
  SingleNode *next = NULL;

  // Constructors
  SingleNode();
  SingleNode(T);
  SingleNode(T, SingleNode *);
  SingleNode(T, SingleNode *, SingleNode *);
};

// SingleNodePtr Definition
template <class T>
using SingleNodePtr = SingleNode<T> *;

// QUEUE LINKED LIST CLASS
// FIFO
// First-in, First-out

template <class T>
class QueueLinkedList
{
protected:
  SingleNodePtr<T> head;
  SingleNodePtr<T> tail;

  int length = 0;
  T error;

  // Private Methods
  void increaseLength();
  void increaseLength(int);
  void decreaseLength();

public:
  // Constructors
  QueueLinkedList(T, T);
  QueueLinkedList(T[], int, T);
  ~QueueLinkedList();

  // Public Methods
  bool isEmpty();
  void push(T);
  T pop(bool);
  T pop();
  T first();
  T last();
  int getLength();
};

// Node Class Constructors
template <class T>
SingleNode<T>::SingleNode()
{
  return;
}

template <class T>
SingleNode<T>::SingleNode(T data)
{
  this->data = data;
}

template <class T>
SingleNode<T>::SingleNode(T data, SingleNode<T> *prev)
{
  this->data = data;

  if (prev != NULL)
    prev->next = this;
}

// QUEUE LINKED LIST CLASS

// Queue Constructors

// Add Head with Only One Next Node
template <class T>
QueueLinkedList<T>::QueueLinkedList(T data, T error)
{
  SingleNodePtr<T> p;

  // Default Error Value
  this->error = error;

  // Create New Node
  p = new SingleNode<T>(data);

  // Set Node as Head and as Tail
  this->tail = this->head = p;

  // Increase Length
  this->increaseLength();
}

// Add Head and Multiple Next Nodes
template <class T>
QueueLinkedList<T>::QueueLinkedList(T data[], int length, T error)
{
  SingleNodePtr<T> p;

  // Default Error Value
  this->error = error;

  // Create First Node
  p = new SingleNode<T>(data[0]);

  // Set p Node as Head
  this->head = p;

  // Add Next Nodes
  for (int i = 1; i < length; i++)
    // Add Node
    p = new SingleNode<T>(data[i], p);

  // Set p Node as Tail
  this->tail = p;

  // Increase Length
  this->increaseLength(length);
}

// Destructor
template <class T>
QueueLinkedList<T>::~QueueLinkedList()
{
  // Remove Node Next to Head if It isn't Empty
  while (!isEmpty())
    this->pop(true);

  // Remove Head Node
  SingleNodePtr<T> temp = this->head;
  this->head = NULL;

  delete[] temp;
}

// Method to Insert Node at Tail
template <class T>
void QueueLinkedList<T>::push(T data)
{
  SingleNodePtr<T> n = new SingleNode<T>(data);

  // Set Node at Tail
  this->tail->next = n;

  // Set Tail
  this->tail = n;

  this->increaseLength();
}

// Method to Remove Head Node
template <class T>
T QueueLinkedList<T>::pop(bool destructor)
{
  SingleNodePtr<T> m, n;

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
T QueueLinkedList<T>::pop()
{
  return this->pop(false);
}

// Method to Get First Node Data
template <class T>
T QueueLinkedList<T>::first()
{
  // Check pos
  if (this->isEmpty())
    return this->error;

  return this->head->data;
}

// Method to Get Last Node Data
template <class T>
T QueueLinkedList<T>::last()
{
  // Check pos
  if (this->isEmpty())
    return this->error;

  return this->tail->data;
}

// Method to Check if Linked List is Empty
template <class T>
bool QueueLinkedList<T>::isEmpty()
{
  return this->head == NULL;
}

// Method to Increase Linked List Length
template <class T>
void QueueLinkedList<T>::increaseLength()
{
  this->length += 1;
}

template <class T>
void QueueLinkedList<T>::increaseLength(int length)
{
  this->length += length;
}

// Method to Decrease Linked List Length
template <class T>
void QueueLinkedList<T>::decreaseLength()
{
  this->length -= 1;
}

// Method to Get Linked List Length
template <class T>
int QueueLinkedList<T>::getLength()
{
  return this->length;
}

#endif