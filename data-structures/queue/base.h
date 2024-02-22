#include <cstdlib>

#include "../single-linked-lists/base.h"

#ifndef QUEUE_LINKED_LISTS
#define QUEUE_LINKED_LISTS

// SingleNodePtr Definition
template <class NodeType>
using SingleNodePtr = SingleNode<NodeType> *;

// QUEUE LINKED LIST CLASS
// FIFO
// First-in, First-out

template <class NodeType>
class QueueLinkedList
{
protected:
  SingleNodePtr<NodeType> head = NULL;
  SingleNodePtr<NodeType> tail = NULL;

  int length = 0;
  NodeType error;

  // Protected Methods
  void increaseLength();
  void increaseLength(int);
  void decreaseLength();
  NodeType pop(bool);

public:
  // Constructors
  QueueLinkedList(NodeType);
  QueueLinkedList(NodeType, NodeType);
  QueueLinkedList(NodeType[], int, NodeType);
  QueueLinkedList(SingleLinkedList<NodeType>, NodeType);
  ~QueueLinkedList();

  // Public Methods
  NodeType pop() { return pop(false); };

  NodeType setNULL(bool);
  NodeType getError();
  bool isEmpty();
  void enqueue(NodeType);
  void push(NodeType);
  NodeType dequeue();
  NodeType first();
  NodeType last();
  int getLength();
};

// Queue Constructors

// Create Queue Linked List and Set Error Value
template <class NodeType>
QueueLinkedList<NodeType>::QueueLinkedList(NodeType error)
{
  // Default Error Value
  this->error = error;
}

// Add Head with Only One Next Node
template <class NodeType>
QueueLinkedList<NodeType>::QueueLinkedList(NodeType data, NodeType error)
{
  SingleNodePtr<NodeType> p;

  // Default Error Value
  this->error = error;

  // Create New Node
  p = new SingleNode<NodeType>(data);

  // Set Node as Head and as Tail
  this->tail = this->head = p;

  // Increase Length
  this->increaseLength();
}

// Add Head and Multiple Next Nodes through an Array
template <class NodeType>
QueueLinkedList<NodeType>::QueueLinkedList(NodeType data[], int length, NodeType error)
{
  SingleNodePtr<NodeType> p;

  // Default Error Value
  this->error = error;

  // Create First Node
  p = new SingleNode<NodeType>(data[0]);

  // Set p Node as Head
  this->head = p;

  // Add Next Nodes
  for (int i = 1; i < length; i++)
    // Add Node
    p = new SingleNode<NodeType>(data[i], p);

  // Set p Node as Tail
  this->tail = p;

  // Increase Length
  this->increaseLength(length);
}

// Add Head and Multiple Next Nodes through a Single Linked List
template <class NodeType>
QueueLinkedList<NodeType>::QueueLinkedList(SingleLinkedList<NodeType> list, NodeType error)
{
  SingleNodePtr<NodeType> p;
  int length = list.getLength();

  // Default Error Value
  this->error = error;

  // Create First Node
  p = new SingleNode<NodeType>(list.get(0));

  // Set p Node as Head
  this->head = p;

  // Add Next Nodes
  for (int i = 1; i < length; i++)
    // Add Node
    p = new SingleNode<NodeType>(list.get(i), p);

  // Set p Node as Tail
  this->tail = p;

  // Increase Length
  this->increaseLength(length);
}

// Destructor
template <class NodeType>
QueueLinkedList<NodeType>::~QueueLinkedList()
{
  // Remove Node Next to Head if It isn't Empty
  while (!isEmpty())
    this->pop(true);

  // Remove Head Node
  SingleNodePtr<NodeType> temp = this->head;
  this->head = NULL;

  delete[] temp;
}

// Method to Safely Remove Node that is Both Head and Tail
template <class NodeType>
NodeType QueueLinkedList<NodeType>::setNULL(bool destructor)
{
  SingleNodePtr<NodeType> t;

  // Get Tail
  t = this->tail;

  // Get Tail Data
  NodeType data = t->data;

  // Set Head and Tail Node as NULL
  this->head = this->tail = NULL;

  // Deallocate Memory
  if (destructor)
    delete[] t;
  else
    delete t;

  decreaseLength();

  return data;
}

// Method to Get Error Value
template <class NodeType>
NodeType QueueLinkedList<NodeType>::getError()
{
  return this->error;
}

// Method to Insert Node at Tail
template <class NodeType>
void QueueLinkedList<NodeType>::push(NodeType data)
{
  SingleNodePtr<NodeType> n = new SingleNode<NodeType>(data);

  // Set Head and Tail
  if (this->isEmpty())
    this->head = this->tail = n;
  else
  {
    // Set Next Node to Tail
    this->tail->next = n;

    // Set New Tail
    this->tail = n;
  }

  this->increaseLength();
}

// Calls Push Method
template <class NodeType>
void QueueLinkedList<NodeType>::enqueue(NodeType data)
{
  this->push(data);
}

// Method to Remove Head Node
template <class NodeType>
NodeType QueueLinkedList<NodeType>::pop(bool destructor)
{
  if (this->isEmpty())
    return this->error;

  // Head and Tail Node are the Same
  if (this->getLength() == 1)
    return this->setNULL(destructor);

  SingleNodePtr<NodeType> m, n;

  // Get Head Node
  m = this->head;
  NodeType data = m->data;

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

// Calls Pop Method
template <class NodeType>
NodeType QueueLinkedList<NodeType>::dequeue()
{
  return this->pop(data);
}

// Method to Get First Node Data
template <class NodeType>
NodeType QueueLinkedList<NodeType>::first()
{
  // Check pos
  if (this->isEmpty())
    return this->error;

  return this->head->data;
}

// Method to Get Last Node Data
template <class NodeType>
NodeType QueueLinkedList<NodeType>::last()
{
  // Check pos
  if (this->isEmpty())
    return this->error;

  return this->tail->data;
}

// Method to Check if Linked List is Empty
template <class NodeType>
bool QueueLinkedList<NodeType>::isEmpty()
{
  return this->head == NULL;
}

// Method to Increase Linked List Length
template <class NodeType>
void QueueLinkedList<NodeType>::increaseLength()
{
  this->length += 1;
}

template <class NodeType>
void QueueLinkedList<NodeType>::increaseLength(int length)
{
  this->length += length;
}

// Method to Decrease Linked List Length
template <class NodeType>
void QueueLinkedList<NodeType>::decreaseLength()
{
  this->length -= 1;
}

// Method to Get Linked List Length
template <class NodeType>
int QueueLinkedList<NodeType>::getLength()
{
  return this->length;
}

#endif