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
  SingleNodePtr<NodeType> tail = NULL;

  int length = 0;
  NodeType error;

  // Protected Methods
  void increaseLength(int length) { this->length += length; };
  void increaseLength() { this->increaseLength(1); };
  void decreaseLength() { this->increaseLength(-1); };
  void empty() { this->length = 0; };

  SingleNodePtr<NodeType> move(SingleNodePtr<NodeType>, int);
  SingleNodePtr<NodeType> move(int n) { return move(this->head, n); }; // Set Head as p Node
  NodeType remove(bool);
  NodeType pop(bool);
  NodeType setNULL(bool);

public:
  // Constructors
  CircularSingleLinkedList(NodeType);
  CircularSingleLinkedList(NodeType, NodeType);
  CircularSingleLinkedList(NodeType[], int, NodeType);
  CircularSingleLinkedList(SingleLinkedList<NodeType>, NodeType);
  ~CircularSingleLinkedList();

  // Public Methods
  NodeType getError() { return this->error; };
  int getLength() { return this->length; };
  bool isEmpty() { return this->head == NULL; };

  void push(NodeType);
  void pushBack(NodeType);
  void insertAt(NodeType, int);
  NodeType pop() { return pop(false); };
  NodeType remove() { return remove(false); };
  NodeType removeAt(int);
  NodeType change(NodeType, int);
  NodeType get(int);
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

  // Add Node as Head and Tail
  this->head = this->tail = p;

  // Set Head Next Node to Head Node
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

  // Set p as Tail Node
  this->tail = p;

  // Set Tail Next Node to Head
  this->tail->next = this->head;

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

  // Set p as Tail Node
  this->tail = p;

  // Set Tail Next Node to Head
  this->tail->next = this->head;
}

// Destructor
template <class NodeType>
CircularSingleLinkedList<NodeType>::~CircularSingleLinkedList()
{
  // Remove Head Previous Node if It isn't Empty
  while (!isEmpty())
    this->pop(true);
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

  // Insert Node Before Head
  if (!this->isEmpty())
  {
    // Create New Node and Insert Between Tail Node and Head Node
    h = new SingleNode<NodeType>(data, this->head);
    this->tail->next = h;
  }

  // Create n Node and Self-Reference as Previous and Next Node
  else
  {
    h = new SingleNode<NodeType>(data, NULL);
    h->next = h;

    // Set h Node as Tail
    this->tail = h;
  }

  // Set h Node as Head
  this->head = h;

  this->increaseLength();
}

// Method to Insert Node at Given Position
template <class NodeType>
void CircularSingleLinkedList<NodeType>::insertAt(NodeType data, int pos)
{
  int posRemainder = pos % this->length;

  // Check pos
  if (posRemainder == 0)
  {
    this->push(data); // Insert Node at Head
    return;
  }

  if ((pos >= 0 && posRemainder == this->length - 1) || (pos < 0 && posRemainder == -1))
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
  SingleNodePtr<NodeType> n;

  // Insert Node After Previous Node
  if (!this->isEmpty())
    // Create New Node and Insert Between Head Previous Node and Head Node
    n = new SingleNode<NodeType>(data, this->tail, this->head);

  // Create n Node and Self-Reference as Next Node
  else
  {
    n = new SingleNode<NodeType>(data);
    n->next = n;

    // Set n Node as Head
    this->head = n;
  }

  // Set Tail
  this->tail = n;

  this->increaseLength();
}

// Method to Safely Remove Head Node when it's the Only Node in Circular Single Linked List
template <class NodeType>
NodeType CircularSingleLinkedList<NodeType>::setNULL(bool destructor)
{
  SingleNodePtr<NodeType> h, t;

  // Get Head and Tail Node and Data
  h = this->head;
  t = this->tail;
  NodeType data = h->data;

  // Set Head and Tail as NULL
  this->head = this->tail = NULL;

  // Deallocate Memory
  if (destructor)
    delete[] t, h;
  else
    delete t, h;

  this->decreaseLength();

  return data;
}

// Method to Remove Head Node
template <class NodeType>
NodeType CircularSingleLinkedList<NodeType>::remove(bool destructor)
{
  SingleNodePtr<NodeType> p, m, n;

  // Check if It's Empty
  if (this->isEmpty())
    return this->error;

  // Circular Single Linked List Only have One Node which is Head
  if (this->getLength() == 1)
    return this->setNULL(destructor);

  // Get Head Node and Data
  m = this->head;
  NodeType data = m->data;

  // Get Previous and Next Node to the One that will be Removed
  p = this->tail;
  n = m->next;

  // Remove m Node from Circular Single Linked List
  p->next = n;
  this->head = n;

  // Deallocate Memory
  if (destructor)
    delete[] m;
  else
    delete m;

  this->decreaseLength();

  return data;
}

// Method to Remove Node at Head Previous Node
template <class NodeType>
NodeType CircularSingleLinkedList<NodeType>::pop(bool destructor)
{
  SingleNodePtr<NodeType> p, t;

  // Check if It's Empty
  if (this->isEmpty())
    return this->error;

  // Circular Single Linked List Only have One Node which is Head
  if (this->getLength() == 1)
    return this->setNULL(destructor);

  // Move from Head Node to Next Node pos-2 Times. Get Previous Node to the One to be Removed
  p = this->move(this->length - 2);

  // Get Tail Node and Data
  t = this->tail;
  NodeType data = t->data;

  // Set p Next Node to Head
  p->next = this->head;

  // Deallocate Memory
  if (destructor)
    delete[] t;
  else
    delete t;

  this->decreaseLength();

  return data;
}

// Method to Remove Node at Given Index
template <class NodeType>
NodeType CircularSingleLinkedList<NodeType>::removeAt(int pos)
{
  int posRemainder = pos % posRemainder;

  // Check if It's Empty
  if (this->isEmpty())
    return this->error; // Node not Found

  if (posRemainder == 0)
    return this->remove(); // Remove Node at Head

  if ((pos >= 0 && posRemainder == this->length - 1) || (pos < 0 && posRemainder == -1))
    return this->pop(); // Remove Node at Tail

  SingleNodePtr<NodeType> p, m, n;

  // Move from Head Node to Next Node pos-1 Times. Get Previous Node to the One to be Removed
  p = this->move(pos - 1);

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
NodeType CircularSingleLinkedList<NodeType>::change(NodeType data, int pos)
{
  // Check if It's Empty
  if (this->isEmpty())
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
  int posRemainder = pos % posRemainder;

  // Check if It's Empty
  if (this->isEmpty())
    return this->error;

  // Check pos
  if (posRemainder == 0)
    return this->head->data; // Get Head Node Data

  if ((pos >= 0 && posRemainder == this->length - 1) || (pos < 0 && posRemainder == -1))
    return this->tail->data; // Get Tail Node Data

  if (pos < 0)
    pos += this->length; // Get Position

  SingleNodePtr<NodeType> n;

  // Move from Head Node to Next Node pos Times
  n = this->move(pos);

  // Return Value
  return n->data;
}

// Method to Concat Circular Single Linked Lists
template <class NodeType>
void CircularSingleLinkedList<NodeType>::concat(CircularSingleLinkedList<NodeType> *l)
{
  SingleNodePtr<NodeType> t;

  // Check if l is Empty
  if (l->isEmpty())
    return;

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