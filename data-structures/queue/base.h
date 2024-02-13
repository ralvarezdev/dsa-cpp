#include <cstdlib>

#include "../nodes/singleNode.h"

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

  // Private Methods
  void increaseLength();
  void increaseLength(int);
  void decreaseLength();

public:
  // Constructors
  QueueLinkedList(NodeType);
  QueueLinkedList(NodeType, NodeType);
  QueueLinkedList(NodeType[], int, NodeType);
  ~QueueLinkedList();

  // Public Methods
  NodeType getError();
  bool isEmpty();
  void push(NodeType);
  NodeType pop(bool);
  NodeType pop();
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

// Add Head and Multiple Next Nodes
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

  // Set Node at Tail
  this->tail->next = n;

  // Set Tail
  this->tail = n;

  // Set Head
  if (this->isEmpty())
    this->head = n;

  this->increaseLength();
}

// Method to Remove Head Node
template <class NodeType>
NodeType QueueLinkedList<NodeType>::pop(bool destructor)
{
  if (this->isEmpty())
    return this->error;

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

// Method Overloads
template <class NodeType>
NodeType QueueLinkedList<NodeType>::pop()
{
  return this->pop(false);
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