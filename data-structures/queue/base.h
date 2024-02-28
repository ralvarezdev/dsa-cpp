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
  void increaseLength(int length) { this->length += length; };
  void increaseLength() { this->increaseLength(1); };
  void decreaseLength() { this->increaseLength(-1); };

  NodeType setNULL();

public:
  // Constructors
  QueueLinkedList(NodeType);
  QueueLinkedList(NodeType, NodeType);
  QueueLinkedList(NodeType[], int, NodeType);
  QueueLinkedList(SingleLinkedList<NodeType> *, NodeType);

  // Destructor
  virtual ~QueueLinkedList()
  {
    // Remove Top Node if It isn't Empty
    while (!this->isEmpty())
      this->pop();
  }

  // Public Method
  NodeType getError() { return this->error; };
  int getLength() { return this->length; };
  bool isEmpty() { return this->length == 0; };

  void push(NodeType);
  void enqueue(NodeType data) { push(data); }; // Calls Push Method
  NodeType pop();
  NodeType dequeue() { return pop(); }; // Calls Pop Method
  NodeType first();
  NodeType last();
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
QueueLinkedList<NodeType>::QueueLinkedList(SingleLinkedList<NodeType> *list, NodeType error)
{
  SingleNodePtr<NodeType> p;
  int length = list->getLength();

  // Default Error Value
  this->error = error;

  // Create First Node
  p = new SingleNode<NodeType>(list->get(0));

  // Set p Node as Head
  this->head = p;

  // Add Next Nodes
  for (int i = 1; i < length; i++)
    // Add Node
    p = new SingleNode<NodeType>(list->get(i), p);

  // Set p Node as Tail
  this->tail = p;

  // Increase Length
  this->increaseLength(length);
}

// Method to Safely Remove Node that is Both Head and Tail
template <class NodeType>
NodeType QueueLinkedList<NodeType>::setNULL()
{
  SingleNodePtr<NodeType> t;

  // Get Tail
  t = this->tail;

  // Get Tail Data
  NodeType data = t->data;

  // Set Head and Tail Node as NULL
  this->head = this->tail = NULL;

  // Deallocate Memory
  delete t;

  decreaseLength();

  return data;
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

// Method to Remove Head Node
template <class NodeType>
NodeType QueueLinkedList<NodeType>::pop()
{
  if (this->isEmpty())
    return this->error;

  // Head and Tail Node are the Same
  if (this->getLength() == 1)
    return this->setNULL();

  SingleNodePtr<NodeType> m, n;

  // Get Head Node
  m = this->head;
  NodeType data = m->data;

  // Get Next Node to the One that will be Removed
  n = m->next;

  // Remove m Node from Stack
  this->head = n;

  // Deallocate Memory
  delete m;

  decreaseLength();

  return data;
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

#endif