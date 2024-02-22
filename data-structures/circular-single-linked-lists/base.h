#include <cstdlib>
#include <math.h>

#include "../single-linked-lists/base.h"

using std::abs;

#ifndef CIRCULAR_SINGLE_LINKED_LISTS
#define CIRCULAR_SINGLE_LINKED_LISTS

// CIRCULAR SINGLE LINKED LIST CLASS

template <class NodeType>
class CircularSingleLinkedList
{
protected:
  SingleNodePtr<NodeType> head = NULL;

  int length = 0;
  NodeType error;

  // Protected Methods
  void increaseLength();
  void increaseLength(int);
  void decreaseLength();
  SingleNodePtr<NodeType> move(SingleNodePtr<NodeType>, int);
  SingleNodePtr<NodeType> move(int n) { return move(head, n); };         // Set Head as p Node
  SingleNodePtr<NodeType> moveToHeadPrevNode() { return move(length); }; // Get Head Previous Node
  NodeType remove(bool);
  NodeType pop(bool);
  NodeType setNULL(bool);
  void empty() { length = 0; };

public:
  // Constructors
  CircularSingleLinkedList(NodeType);
  CircularSingleLinkedList(NodeType, NodeType);
  CircularSingleLinkedList(NodeType[], int, NodeType);
  CircularSingleLinkedList(SingleLinkedList<NodeType>, NodeType);
  ~CircularSingleLinkedList();

  // Public Methods
  NodeType getError();
  bool isEmpty();
  void push(NodeType);
  void pushBack(NodeType);
  void insertAt(NodeType, int);
  NodeType pop() { return pop(false); };
  NodeType removeAt(int);
  NodeType remove() { return remove(false); };
  NodeType change(NodeType, int);
  NodeType get(int);
  int getLength();
  void concat(CircularSingleLinkedList *);
};

// Circular Single Linked List Constructors

// Create Circular Single Linked List and Set Error Value
template <class NodeType>
CircularSingleLinkedList<NodeType>::CircularSingleLinkedList(NodeType error)
{
  // Default Error Value
  this->error = error;
}

// Add Head with Only One Next Node
template <class NodeType>
CircularSingleLinkedList<NodeType>::CircularSingleLinkedList(NodeType data, NodeType error)
{
  SingleNodePtr<NodeType> p;

  // Default Error Value
  this->error = error;

  // Create New Node
  p = new SingleNode<NodeType>(data);

  // Set Node as Head
  this->head = p;

  // Set Head as Head Next Node
  this->head->next = this->head;

  // Increase Length
  this->increaseLength();
}

// Add Head and Multiple Next Nodes through an Array
template <class NodeType>
CircularSingleLinkedList<NodeType>::CircularSingleLinkedList(NodeType data[], int length, NodeType error)
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
  {
    // Add Node
    p->next = new SingleNode<NodeType>(data[i]);

    // Move to Next Node
    p = p->next;
  }

  // Set p Next Node to Head
  p->next = this->head;

  // Increase Length
  this->increaseLength(length);
}

// Add Head and Multiple Next Nodes through an Single Linked list
template <class NodeType>
CircularSingleLinkedList<NodeType>::CircularSingleLinkedList(SingleLinkedList<NodeType> list, NodeType error)
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
  {
    // Add Node
    p->next = new SingleNode<NodeType>(list.get[i]);

    // Move to Next Node
    p = p->next;
  }

  // Set p Next Node to Head
  p->next = this->head;

  // Increase Length
  this->increaseLength(length);
}

// Destructor
template <class NodeType>
CircularSingleLinkedList<NodeType>::~CircularSingleLinkedList()
{
  // Remove Head Previous Node if It isn't Empty
  while (!isEmpty())
    this->pop(true);
}

// Method to Get Error Value
template <class NodeType>
NodeType CircularSingleLinkedList<NodeType>::getError()
{
  return this->error;
}

// Method to Move to Next Node N Times
template <class NodeType>
SingleNodePtr<NodeType> CircularSingleLinkedList<NodeType>::move(SingleNodePtr<NodeType> p, int n)
{
  // Move to Next N Nodes
  for (int i = 0; i < n; i++)
    p = p->next;

  return p;
}

// Method to Insert Node Before Head
template <class NodeType>
void CircularSingleLinkedList<NodeType>::push(NodeType data)
{
  SingleNodePtr<NodeType> h, t;

  // Get Head Previous Node
  t = this->moveToHeadPrevNode();

  // Insert Node Before Head
  if (this->isEmpty())
  {
    h = new SingleNode<NodeType>(data, NULL);
    h->next = h;
  }
  else
    h = new SingleNode<NodeType>(data, this->head);

  // Set h Node as Head
  this->head = h;

  this->increaseLength();
}

// Method to Insert Node at Given Position
template <class NodeType>
void CircularSingleLinkedList<NodeType>::insertAt(NodeType data, int pos)
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

  SingleNodePtr<NodeType> p, n;

  // Move to Next or Prev Node pos Times
  p = this->move(pos);

  // Get Next Node
  n = p->next;

  // Create New Node
  new SingleNode<NodeType>(data, p, n);

  this->increaseLength();
}

// Method to Insert Node at Head Previous Node
template <class NodeType>
void CircularSingleLinkedList<NodeType>::pushBack(NodeType data)
{
  // Create New Node and Assign Old Head Previous Node as Previous Node
  SingleNodePtr<NodeType> n = new SingleNode<NodeType>(data, this->head->prev, this->head);

  // Set Head if it's NULL
  if (this->head == NULL)
  {
    h->prev = h->next = h;
    this->head = h;
  }

  this->increaseLength();
}

// Method to Safely Remove Head Node when it's the Only Node in Circular Single Linked List
template <class NodeType>
NodeType CircularSingleLinkedList<NodeType>::setNULL(bool destructor)
{
  SingleNodePtr<NodeType> h;

  // Get Head Node
  h = this->head;

  // Get Head Data
  NodeType data = h->data;

  // Set Head as NULL
  this->head = NULL;

  // Deallocate Memory
  if (destructor)
    delete[] h;
  else
    delete h;

  decreaseLength();

  return data;
}

// Method to Remove Head Node
template <class NodeType>
NodeType CircularSingleLinkedList<NodeType>::remove(bool destructor)
{
  SingleNodePtr<NodeType> m, n;

  if (this->isEmpty())
    return this->error;

  // Circular Single Linked List Only have One Node which is Head
  if (this->getLength() == 1)
    return this->setNULL(destructor);

  // Get Head Node
  m = this->head;
  NodeType data = m->data;

  // Get Next Node to the One that will be Removed
  n = m->next;

  // Remove m Node from Circular Single Linked List
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

// Method to Remove Node at Head Previous Node
template <class NodeType>
NodeType CircularSingleLinkedList<NodeType>::pop(bool destructor)
{
  if (this->isEmpty())
    return this->error;

  // Circular Single Linked List Only have One Node which is Head
  if (this->getLength() == 1)
    return this->setNULL(destructor);

  SingleNodePtr<NodeType> t, p;

  this->decreaseLength();

  // Set Head Previous Node as Tail;
  t = this->head->prev;

  // Get Tail Previous Node
  p = t->prev;

  // Get Tail Data
  NodeType data = t->data;

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

// Method to Remove Node at Given Index
template <class NodeType>
NodeType CircularSingleLinkedList<NodeType>::removeAt(int pos)
{
  // Check pos
  if (pos == -1 || pos >= this->length)
    return this->error; // Node not Found

  if (pos == 0)
    return this->remove(); // Remove Node at Head

  if (pos == this->length - 1)
    return this->pop(); // Remove Tail

  pos -= 1;

  SingleNodePtr<NodeType> p, m, n;

  this->decreaseLength();

  // Move to Next Node pos Times
  p = this->move(pos);

  // Get Node to Remove
  m = p->next;

  // Remove Node
  n = m->next;
  NodeType data = m->data;
  p->next = n;
  n->prev = p;

  // Deallocate Memory
  delete m;

  return data;
}

// Method to Modify Node Value at Given Position
template <class NodeType>
NodeType CircularSingleLinkedList<NodeType>::change(NodeType data, int pos)
{
  if (this->isEmpty() || pos >= this->length || abs(pos) >= this->length + 1)
    return this->error; // Node not Found

  // Move to Node
  SingleNodePtr<NodeType> m = this->move(pos);

  // Get Old Value
  NodeType old = m->data;

  // Assign New Value
  m->data = data;

  return old;
}

// Method to Get Node at Given Position
template <class NodeType>
NodeType CircularSingleLinkedList<NodeType>::get(int pos)
{
  // Check pos
  if (this->isEmpty())
    return this->error;

  if (pos == 0)
    return this->head->data; // Get Node Next to Head

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

// Method to Check if Circular Single Linked List is Empty
template <class NodeType>
bool CircularSingleLinkedList<NodeType>::isEmpty()
{
  return this->head == NULL;
}

// Method to Increase Circular Single Linked List Length
template <class NodeType>
void CircularSingleLinkedList<NodeType>::increaseLength()
{
  this->length += 1;
}

template <class NodeType>
void CircularSingleLinkedList<NodeType>::increaseLength(int length)
{
  this->length += length;
}

// Method to Decrease Circular Single Linked List Length
template <class NodeType>
void CircularSingleLinkedList<NodeType>::decreaseLength()
{
  this->length -= 1;
}

// Method to Get Circular Single Circular Single Linked List Length
template <class NodeType>
int CircularSingleLinkedList<NodeType>::getLength()
{
  return this->length;
}

// Method to Concat Circular Single Linked Lists
template <class NodeType>
void CircularSingleLinkedList<NodeType>::concat(CircularSingleLinkedList<NodeType> *l)
{
  SingleNodePtr<NodeType> t;

  // Get Head Previous Node
  t = this->moveToHeadPrevNode();

  // Assign l First Node Next to this Single Linked List Tail
  t->next = l->head->next;

  // Save New Length
  this->increaseLength(l->getLength());

  // Set l Head and Tail Node to NULL
  l->head = NULL;

  // Set l Length to 0
  l->empty();
}

#endif