#include <cstdlib>

#include "../nodes/singleNode.h"

#ifndef SINGLE_LINKED_LISTS
#define SINGLE_LINKED_LISTS

// SINGLE LINKED LIST CLASS

template <class NodeType>
class SingleLinkedList
{
protected:
  SingleNodePtr<NodeType> head = NULL;
  SingleNodePtr<NodeType> tail = NULL;
  // SingleNodePtr<NodeType> curr = NULL;

  int length = 0;
  NodeType error;

  // Protected Methods
  void increaseLength(int length) { this->length += length; };
  void increaseLength() { this->increaseLength(1); };
  void decreaseLength() { this->increaseLength(-1); };
  void empty() { this->length = 0; };

  SingleNodePtr<NodeType> move(SingleNodePtr<NodeType>, int);
  SingleNodePtr<NodeType> move(int n) { return move(this->head, n); }; // Set Head as p Node

public:
  // Constructors
  SingleLinkedList(NodeType);
  SingleLinkedList(NodeType, NodeType);
  SingleLinkedList(NodeType[], int, NodeType);

  // Destructor
  virtual ~SingleLinkedList()
  {
    // Remove Node Next to Head if It isn't Empty
    while (!this->isEmpty())
      this->remove();

    // Remove Head Node
    SingleNodePtr<NodeType> temp = this->head;
    this->head = NULL;

    delete temp;
  }

  // Public Methods
  NodeType getError() { return this->error; };
  int getLength() { return this->length; };
  bool isEmpty() { return this->length == 0; };

  void push(NodeType);
  void pushBack(NodeType);
  void insertAt(NodeType, int);
  NodeType pop();
  NodeType remove();
  NodeType removeAt(int);
  NodeType change(NodeType, int);
  NodeType get(int);
  void concat(SingleLinkedList *);
  NodeType removeBack();

  // void setCurrent(SingleNodePtr<NodeType>);
  // void setCurrent();
  // int count(SingleNodePtr<NodeType>);
};

// Single Linked List Constructors

// Add Head with Next Node as NULL
template <class NodeType>
SingleLinkedList<NodeType>::SingleLinkedList(NodeType error)
{
  // Default Error Value
  this->error = error;

  // Add Node as Head and Tail
  this->head = this->tail = new SingleNode<NodeType>();
}

// Add Head with Only One Next Node
template <class NodeType>
SingleLinkedList<NodeType>::SingleLinkedList(NodeType data, NodeType error)
{
  SingleNodePtr<NodeType> p;

  // Default Error Value
  this->error = error;

  // Add Head Node
  this->head = new SingleNode<NodeType>();

  // Add Next Node
  p = new SingleNode<NodeType>(data);

  // Add Node as Head Next Node and as Tail
  this->tail = this->head->next = p;

  // Increase Length
  this->increaseLength();
}

// Add Head and Multiple Next Nodes
template <class NodeType>
SingleLinkedList<NodeType>::SingleLinkedList(NodeType data[], int length, NodeType error)
{
  SingleNodePtr<NodeType> p;

  // Default Error Value
  this->error = error;

  // Add Head
  this->head = p = new SingleNode<NodeType>();

  // Add Next Nodes
  for (int i = 0; i < length; i++)
  {
    // Add Node
    p->next = new SingleNode<NodeType>(data[i]);

    // Move to Next Node
    p = p->next;
  }

  // Set p Node as Tail
  this->tail = p;

  // Increase Length
  this->increaseLength(length);
}

// Method to Move to Next Node N Times
template <class NodeType>
SingleNodePtr<NodeType> SingleLinkedList<NodeType>::move(SingleNodePtr<NodeType> p, int n)
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
template <class NodeType>
void SingleLinkedList<NodeType>::push(NodeType data)
{
  SingleNodePtr<NodeType> n, p;

  // Insert Node Next to Head
  n = this->head->next;
  p = new SingleNode<NodeType>(data, n);

  // Set Tail if It's NULL
  if (this->isEmpty())
    this->tail = p;

  // Set Node Next to Head
  this->head->next = p;

  this->increaseLength();
}

// Method to Insert Node at Given Position
template <class NodeType>
void SingleLinkedList<NodeType>::insertAt(NodeType data, int pos)
{
  // Check pos
  if (pos < 0)
    pos += this->length + 1; // Get Position

  // Check if It's Empty
  if (this->isEmpty() && pos > 0)
    return; // pos Out of Range

  if (pos > this->length || pos < 0)
    return; // pos Out of Range

  if (pos == 0)
  {
    this->push(data); // Insert Node Next to Head
    return;
  }

  if (pos == this->length)
  {
    this->pushBack(data); // Insert Node at Tail
    return;
  }

  SingleNodePtr<NodeType> p;

  // Move from Head Node to Next Node pos Times
  p = this->move(pos);

  // pos is Out of Range
  if (p == NULL)
    return;

  // Create New Node Between p and p Next Node
  new SingleNode<NodeType>(data, p, p->next);

  this->increaseLength();
}

// Method to Insert Node at Tail
template <class NodeType>
void SingleLinkedList<NodeType>::pushBack(NodeType data)
{
  SingleNodePtr<NodeType> n = new SingleNode<NodeType>(data, this->tail, NULL);

  // Set Head Next Node if It's NULL
  if (this->isEmpty())
    this->head->next = n;

  // Set Tail
  this->tail = n;

  this->increaseLength();
}

// Method to Remove Node Next to Head
template <class NodeType>
NodeType SingleLinkedList<NodeType>::remove()
{
  // Check if It's Empty
  if (this->isEmpty())
    return this->error;

  // Get Node Next to Head
  SingleNodePtr<NodeType> n = this->head->next;
  NodeType data = n->data;

  // Remove n Node from Single Linked List
  this->head->next = n->next;

  // Deallocate Memory
  delete n;

  this->decreaseLength();

  return data;
}

// Method to Remove Node at Tail
template <class NodeType>
NodeType SingleLinkedList<NodeType>::pop()
{
  // Check if It's Empty
  if (this->isEmpty())
    return this->error;

  SingleNodePtr<NodeType> t, p;

  // Move from Head Node to Tail Previous Node
  p = this->move(this->length - 1);

  // Get Tail Node and Data
  t = this->tail;
  NodeType data = t->data;

  // Remove Tail Node
  p->next = NULL;

  // Set Previous Node as Tail
  this->tail = p;

  // Deallocate Memory
  delete t;

  this->decreaseLength();

  return data;
}

// Method to Remove Node at Given Index
template <class NodeType>
NodeType SingleLinkedList<NodeType>::removeAt(int pos)
{
  // Check if It's Empty
  if (this->isEmpty())
    return this->error;

  // Check pos
  if (pos < 0)
    pos += this->length; // Get Position

  if (pos >= this->length || pos < 0)
    return this->error; // Node not Found

  if (pos == 0)
    return this->remove(); // Remove Node Next to Head

  if (pos == this->length - 1)
    return this->pop(); // Remove Tail

  SingleNodePtr<NodeType> p, m, n;

  // Move from Head Node to Next Node pos Times. Get Previous Node to the One to be Removed
  p = this->move(pos);

  // pos is Out of Range
  if (p == NULL)
    return this->error;

  // Get Node and Data to Remove
  m = p->next;
  NodeType data = m->data;

  // Remove Node
  n = m->next;
  p->next = n;

  // Deallocate Memory
  delete m;

  this->decreaseLength();

  return data;
}

// Method to Modify Node Value at Given Position
template <class NodeType>
NodeType SingleLinkedList<NodeType>::change(NodeType data, int pos)
{
  SingleNodePtr<NodeType> n;
  NodeType old;

  // Check if It's Empty
  if (this->isEmpty())
    return this->error;

  // Check pos
  if (pos < 0)
    pos += this->length; // Get Position

  if (pos >= this->length)
    return this->error; // Node not Found

  if (pos == 0)
  {
    old = this->head->next->data;
    this->head->next->data = data; // Change Value to Node Next to Head
    return old;
  }

  if (pos == this->length - 1)
  {
    old = this->tail->data;
    this->tail->data = data; // Change Value to Tail
    return old;
  }

  // Move from Head Next Node to Next Node pos Times
  n = this->move(this->head->next, pos);

  // pos is Out of Range
  if (n == NULL)
    return this->error;

  // Assign New Value
  old = n->data;
  n->data = data;

  return old;
}

// Method to Get Node at Given Position
template <class NodeType>
NodeType SingleLinkedList<NodeType>::get(int pos)
{
  // Check if It's Empty
  if (this->isEmpty())
    return this->error;

  // Check pos
  if (pos < 0)
    pos += this->length; // Get Position

  if (pos >= this->length)
    return this->error; // Node not Found

  if (pos == 0)
    return this->head->next->data; // Get Head Next Node Data

  if (pos == this->length - 1)
    return this->tail->data; // Get Tail Node Data

  // Move from Head Next Node to Next Node pos Times
  SingleNodePtr<NodeType> n = this->move(this->head->next, pos);

  // pos is Out of Range
  if (n == NULL)
    return this->error;

  // Return Value
  return n->data;
}

// Method to Concat Two Single Linked Lists
template <class NodeType>
void SingleLinkedList<NodeType>::concat(SingleLinkedList<NodeType> *l)
{
  // Check if l is Empty
  if (l->isEmpty())
    return;

  // Assign l First Node Next to this Single Linked List Tail
  this->tail->next = l->head->next;

  // Save New Tail Node
  this->tail = l->tail;

  // Save New Length
  this->increaseLength(l->getLength());

  // Set l Head and Tail Node to NULL
  l->head = l->tail = NULL;

  // Set l Length to 0
  l->empty();
}

// Method to Get First Node Data and Push it Back
template <class NodeType>
NodeType SingleLinkedList<NodeType>::removeBack()
{
  NodeType data;

  // Get First Node Data
  data = this->remove();

  // Push Back Node Data
  this->pushBack(data);

  return data;
}

/*
// Method to Set Current Node
template <class NodeType>
void SingleLinkedList<NodeType>::setCurrent(SingleNodePtr<NodeType> p)
{
  this->curr = p;
}

// Method Overload to Set Head Node as Current Node
template <class NodeType>
void SingleLinkedList<NodeType>::setCurrent()
{
  this->curr = this->head;
}
*/

/*
// Count Nodes with a Recursive Method
template <class NodeType>
int SingleLinkedList<NodeType>::count(SingleNodePtr<NodeType> p)
{
  if (p != NULL)
    return count(p->next) + 1;

  // Set Head Node as Current Node
  this->setCurrent();

  return 0;
}
*/

#endif