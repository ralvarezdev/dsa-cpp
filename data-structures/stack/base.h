#include <cstdlib>

#include "../single-linked-lists/base.h"

#ifndef STACK_LINKED_LISTS
#define STACK_LINKED_LISTS

// SingleNodePtr Definition
template <class NodeType>
using SingleNodePtr = SingleNode<NodeType> *;

// STACK LINKED LIST CLASS
// LIFO
// Last-in, First-out

template <class NodeType>
class StackLinkedList
{
protected:
  SingleNodePtr<NodeType> head = NULL;

  int length = 0;
  NodeType error;

  // Protected Methods
  void increaseLength(int length) { this->length += length; };
  void increaseLength() { this->increaseLength(1); };
  void decreaseLength() { this->increaseLength(-1); };

public:
  // Constructors
  StackLinkedList(NodeType);
  StackLinkedList(NodeType, NodeType);
  StackLinkedList(NodeType[], int, NodeType);
  StackLinkedList(SingleLinkedList<NodeType> *, NodeType);

  // Destructor
  ~StackLinkedList()
  {
    // Remove Head Node if It isn't Empty
    while (!this->isEmpty())
      this->pop();
  }

  // Public Methods
  NodeType getError() { return this->error; };
  int getLength() { return this->length; };
  bool isEmpty() { return this->length == 0; };

  void push(NodeType);
  NodeType pop();
  NodeType top();
};

// Stack Constructors

// Create Stack Linked List and Set Error Value
template <class NodeType>
StackLinkedList<NodeType>::StackLinkedList(NodeType error)
{
  // Default Error Value
  this->error = error;
}

// Add Head with Only One Next Node
template <class NodeType>
StackLinkedList<NodeType>::StackLinkedList(NodeType data, NodeType error)
{
  // Default Error Value
  this->error = error;

  // Create New Node and Assign It as Head Node
  this->head = new SingleNode<NodeType>(data);

  // Increase Length
  this->increaseLength();
}

// Add Head and Multiple Next Nodes through an Array
template <class NodeType>
StackLinkedList<NodeType>::StackLinkedList(NodeType data[], int length, NodeType error)
{
  // Default Error Value
  this->error = error;

  // Create First Node
  this->head = new SingleNode<NodeType>(data[0]);

  // Add Next Nodes
  for (int i = 1; i < length; i++)
    // Add Node
    this->head = new SingleNode<NodeType>(data[i], this->head);

  // Increase Length
  this->increaseLength(length);
}

// Add Head and Multiple Next Nodes through a Single Linked List
template <class NodeType>
StackLinkedList<NodeType>::StackLinkedList(SingleLinkedList<NodeType> *list, NodeType error)
{
  int length = list->getLength();

  // Default Error Value
  this->error = error;

  // Create First Node
  this->head = new SingleNode<NodeType>(list->get(0));

  // Add Next Nodes
  for (int i = 1; i < length; i++)
    // Add Node
    this->head = new SingleNode<NodeType>(list->get(i), this->head);

  // Increase Length
  this->increaseLength(length);
}

// Method to Insert Node Before Head
template <class NodeType>
void StackLinkedList<NodeType>::push(NodeType data)
{
  // Insert Node Before Head
  SingleNodePtr<NodeType> h = new SingleNode<NodeType>(data, this->head);

  // Set h Node as Head
  this->head = h;

  this->increaseLength();
}

// Method to Remove Head Node
template <class NodeType>
NodeType StackLinkedList<NodeType>::pop()
{
  SingleNodePtr<NodeType> m, n;

  if (this->isEmpty())
    return this->error;

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

// Method to Get Node Data at Top Position
template <class NodeType>
NodeType StackLinkedList<NodeType>::top()
{
  // Check pos
  if (this->isEmpty())
    return this->error;

  return this->head->data;
}

#endif