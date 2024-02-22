#include <cstdlib>

#include "../nodes/singleNode.h"

#ifndef SINGLE_LINKED_LISTS
#define SINGLE_LINKED_LISTS

// SingleNodePtr Definition
template <class NodeType>
using SingleNodePtr = SingleNode<NodeType> *;

// SINGLE LINKED LIST CLASS

template <class NodeType>
class SingleLinkedList
{
protected:
  SingleNodePtr<NodeType> head;
  SingleNodePtr<NodeType> tail;
  // SingleNodePtr<NodeType> curr = NULL;

  int length = 0;
  NodeType error;

  // Protected Methods
  void increaseLength();
  void increaseLength(int);
  void decreaseLength();
  SingleNodePtr<NodeType> move(SingleNodePtr<NodeType>, int);
  SingleNodePtr<NodeType> move(int n) { return move(this->head, n); }; // Set Head as p Node
  NodeType remove(bool);
  void empty() { this->length = 0; };

public:
  // Constructors
  SingleLinkedList(NodeType);
  SingleLinkedList(NodeType, NodeType);
  SingleLinkedList(NodeType[], int, NodeType);
  ~SingleLinkedList();

  // Public Methods
  NodeType getError();
  bool isEmpty();
  void push(NodeType);
  void pushBack(NodeType);
  void insertAt(NodeType, int);
  NodeType pop();
  NodeType removeAt(int);
  NodeType remove() { return remove(false); };
  NodeType change(NodeType, int);
  NodeType get(int);
  int getLength();
  void concat(SingleLinkedList *);

  // void setCurrent(SingleNodePtr<NodeType>);
  // void setCurrent();
  // int count(SingleNodePtr<NodeType>);
};

// Single Linked List Constructors

// Add Head with Next Node as NULL
template <class NodeType>
SingleLinkedList<NodeType>::SingleLinkedList(NodeType error)
{
  SingleNodePtr<NodeType> p;

  // Default Error Value
  this->error = error;

  // Add Node as Head and Tail
  this->head = this->tail = p = new SingleNode<NodeType>();

  /*
    // Set Head as Current Node
    this->setCurrent();
  */
}

// Add Head with Only One Next Node
template <class NodeType>
SingleLinkedList<NodeType>::SingleLinkedList(NodeType data, NodeType error)
{
  SingleNodePtr<NodeType> p;

  // Default Error Value
  this->error = error;

  // Add Head
  this->head = p = new SingleNode<NodeType>();

  // Add Next Node
  p = new SingleNode<NodeType>(data);

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

  /*
    // Set Head as Current Node
    this->setCurrent();
  */
}

// Destructor
template <class NodeType>
SingleLinkedList<NodeType>::~SingleLinkedList()
{
  // Remove Node Next to Head if It isn't Empty
  while (!isEmpty())
    this->remove(true);

  // Remove Head Node
  SingleNodePtr<NodeType> temp = this->head;
  this->head = NULL;

  delete[] temp;
}

// Method to Get Error Value
template <class NodeType>
NodeType SingleLinkedList<NodeType>::getError()
{
  return this->error;
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

  // Set Node as Tail
  if (this->getLength() == 0)
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

  SingleNodePtr<NodeType> p;

  // Move from Head Node to Next Node pos Times
  p = this->move(pos);

  // pos is Out of Range
  if (p == NULL)
    return;

  // Create New Node and Set m as Next Node
  new SingleNode<NodeType>(data, p, p->next);

  this->increaseLength();
}

// Method to Insert Node at Tail
template <class NodeType>
void SingleLinkedList<NodeType>::pushBack(NodeType data)
{
  SingleNodePtr<NodeType> n = new SingleNode<NodeType>(data, this->tail, NULL);

  // Set Tail
  this->tail = n;

  this->increaseLength();
}

// Method to Remove Node Next to Head
template <class NodeType>
NodeType SingleLinkedList<NodeType>::remove(bool destructor)
{
  if (this->isEmpty())
    return this->error;

  // Get Node Next to Head
  SingleNodePtr<NodeType> n = this->head->next;
  NodeType data = n->data;

  // Remove n Node from Single Linked List
  head->next = n->next;

  // Deallocate Memory
  if (destructor)
    delete[] n;
  else
    delete n;

  decreaseLength();

  return data;
}

// Method to Remove Node at Tail
template <class NodeType>
NodeType SingleLinkedList<NodeType>::pop()
{
  if (this->isEmpty())
    return this->error;

  SingleNodePtr<NodeType> t, p;

  this->decreaseLength();

  // Move from Head Node to Tail Previous Node
  p = this->move(this->length);

  // Get Tail
  t = this->tail;
  NodeType data = t->data;
  p->next = NULL;

  // Set Previous Node as Tail
  this->tail = p;

  // Deallocate Memory
  delete t;

  return data;
}

// Method to Remove Node at Given Index
template <class NodeType>
NodeType SingleLinkedList<NodeType>::removeAt(int pos)
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

  SingleNodePtr<NodeType> p, m, n;

  this->decreaseLength();

  // Move from Head Node to Next Node pos Times
  p = this->move(pos);

  // pos is Out of Range
  if (p == NULL)
    return this->error;

  // Get Node to Remove
  m = p->next;

  // Remove Node
  n = m->next;
  NodeType data = m->data;
  p->next = n;

  // Deallocate Memory
  delete m;

  return data;
}

// Method to Modify Node Value at Given Position
template <class NodeType>
NodeType SingleLinkedList<NodeType>::change(NodeType data, int pos)
{
  SingleNodePtr<NodeType> n;
  NodeType old;

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

  // Move from Head Node to Next Node pos Times
  n = this->move(pos);

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

  SingleNodePtr<NodeType> n;

  n = this->head;

  // Move from Head Node to Next Node pos Times
  n = this->move(pos);

  // pos is Out of Range
  if (n == NULL)
    return this->error;

  // Return Value
  return n->data;
}

// Method to Check if Single Linked List is Empty
template <class NodeType>
bool SingleLinkedList<NodeType>::isEmpty()
{
  return this->head->next == NULL;
}

// Method to Increase Single Linked List Length
template <class NodeType>
void SingleLinkedList<NodeType>::increaseLength()
{
  this->length += 1;
}

template <class NodeType>
void SingleLinkedList<NodeType>::increaseLength(int length)
{
  this->length += length;
}

// Method to Decrease Single Linked List Length
template <class NodeType>
void SingleLinkedList<NodeType>::decreaseLength()
{
  this->length -= 1;
}

// Method to Get Single Linked List Length
template <class NodeType>
int SingleLinkedList<NodeType>::getLength()
{
  return this->length;
}

// Method to Concat Two Single Linked Lists
template <class NodeType>
void SingleLinkedList<NodeType>::concat(SingleLinkedList<NodeType> *l)
{
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