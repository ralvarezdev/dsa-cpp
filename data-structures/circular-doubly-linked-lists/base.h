#include <cstdlib>
#include <math.h>

#include "../doubly-linked-lists/base.h"

using std::abs;

#ifndef CIRCULAR_DOUBLY_LINKED_LISTS
#define CIRCULAR_DOUBLY_LINKED_LISTS

// CIRCULAR DOUBLY LINKED LIST CLASS

template <class NodeType>
class CircularDoublyLinkedList
{
protected:
  DoublyNodePtr<NodeType> head = NULL;

  int length = 0;
  NodeType error;

  // Protected Methods
  void increaseLength(int length) { this->length += length; };
  void increaseLength() { this->increaseLength(1); };
  void decreaseLength() { this->increaseLength(-1); };
  void empty() { this->length = 0; };

  DoublyNodePtr<NodeType> move(int);
  NodeType setNULL();

public:
  // Constructors
  CircularDoublyLinkedList(NodeType);
  CircularDoublyLinkedList(NodeType, NodeType);
  CircularDoublyLinkedList(NodeType[], int, NodeType);
  CircularDoublyLinkedList(DoublyLinkedList<NodeType> *, NodeType);

  // Destructor
  virtual ~CircularDoublyLinkedList()
  {
    // Remove Head Previous Node if It isn't Empty
    while (!this->isEmpty())
      this->pop();
  }

  // Public Methods
  NodeType getError() { return this->error; };
  int getLength() { return this->length; };
  bool isEmpty() { return this->length == 0; };

  void push(NodeType);
  void pushBack(NodeType);
  void insertAt(NodeType, int);
  NodeType remove();
  NodeType pop();
  NodeType removeAt(int);
  NodeType change(NodeType, int);
  NodeType get(int);
  void concat(CircularDoublyLinkedList *);
};

// Circular Doubly Linked List Constructors

// Create Circular Doubly Linked List and Set Error Value
template <class NodeType>
CircularDoublyLinkedList<NodeType>::CircularDoublyLinkedList(NodeType error)
{
  // Default Error Value
  this->error = error;
}

// Add Head with Only One Next Node
template <class NodeType>
CircularDoublyLinkedList<NodeType>::CircularDoublyLinkedList(NodeType data, NodeType error)
{
  // Default Error Value
  this->error = error;

  // Create New Node and Assign It as Head Node
  this->head = new DoublyNode<NodeType>(data);

  // Set Head as Head Next Node and as Head Previous Node
  this->head->next = this->head->prev = this->head;

  // Increase Length
  this->increaseLength();
}

// Add Head and Multiple Next Nodes through an Array
template <class NodeType>
CircularDoublyLinkedList<NodeType>::CircularDoublyLinkedList(NodeType data[], int length, NodeType error)
{
  DoublyNodePtr<NodeType> p;

  // Default Error Value
  this->error = error;

  // Create First Node
  p = new DoublyNode<NodeType>(data[0]);

  // Set p Node as Head
  this->head = p;

  // Add Next Nodes
  for (int i = 1; i < length; i++)
    // Add Node
    p = new DoublyNode<NodeType>(data[i], p);

  // Set p Next Node to Head, and Set Head Previous Node to p
  p->next = this->head;
  this->head->prev = p;

  // Increase Length
  this->increaseLength(length);
}

// Add Head and Multiple Next Nodes through an Doubly Linked list
template <class NodeType>
CircularDoublyLinkedList<NodeType>::CircularDoublyLinkedList(DoublyLinkedList<NodeType> *list, NodeType error)
{
  DoublyNodePtr<NodeType> p;
  int length = list->getLength();

  // Default Error Value
  this->error = error;

  // Create First Node
  p = new DoublyNode<NodeType>(list->get(0));

  // Set p Node as Head
  this->head = p;

  // Add Next Nodes
  for (int i = 1; i < length; i++)
    // Add Node
    p = new DoublyNode<NodeType>(list->get(i), p);

  // Set p Next Node to Head, and Set Head Previous Node to p
  p->next = this->head;
  this->head->prev = p;

  // Increase Length
  this->increaseLength(length);
}

// Method to Move to Next Node N Times
template <class NodeType>
DoublyNodePtr<NodeType> CircularDoublyLinkedList<NodeType>::move(int n)
{
  DoublyNodePtr<NodeType> p;
  int mov = n > 0 ? n % this->length : n % this->length + 1;
  bool backwards = n < 0;

  // Works only for Negative n Values
  if (backwards)
    if (abs(mov) < this->length / 2)
      mov = abs(mov); // Get Absolute Value of mov
    else
    {
      backwards = false;
      mov = this->length + mov - 1;
    }
  // Works only for Positive n Values
  else if (mov > this->length / 2)
  {
    backwards = true;
    mov = this->length - mov - 1;
  }

  // Move from Head Previous Node to Head, or from Head to Head Previous Node
  p = backwards ? this->head->prev : this->head;

  if (backwards)
    // Move to Previous N Nodes
    for (int i = 0; i < mov; i++)
      p = p->prev;
  else
    // Move to Next N Nodes
    for (int i = 0; i < mov; i++)
      p = p->next;
  return p;
}

// Method to Insert Node Before Head
template <class NodeType>
void CircularDoublyLinkedList<NodeType>::push(NodeType data)
{
  DoublyNodePtr<NodeType> n;

  // Insert Node Before Head
  if (!this->isEmpty())
    // Create New Node and Insert Between Head Previous Node and Head Node
    n = new DoublyNode<NodeType>(data, this->head->prev, this->head);

  // Create n Node and Self-Reference as Previous and Next Node
  else
  {
    n = new DoublyNode<NodeType>(data);
    n->prev = n->next = n;
  }

  // Set n Node as Head
  this->head = n;

  this->increaseLength();
}

// Method to Insert Node at Given Position
template <class NodeType>
void CircularDoublyLinkedList<NodeType>::insertAt(NodeType data, int pos)
{
  int posRemainder = pos % this->length;

  // Check pos
  if (posRemainder == 0)
  {
    this->push(data); // Insert Node at Head
    return;
  }

  if ((pos > 0 && posRemainder == this->length) || (pos < 0 && posRemainder == -1))
  {
    this->pushBack(data); // Insert Node at Tail
    return;
  }

  if (pos > 0)
    pos -= 1;

  DoublyNodePtr<NodeType> p, n;

  // Move to Next or Previous Node pos Times
  p = this->move(pos);

  // Get Next Node
  n = p->next;

  // Create New Node Between p and n Node
  new DoublyNode<NodeType>(data, p, n);

  this->increaseLength();
}

// Method to Insert Node at Head Previous Node
template <class NodeType>
void CircularDoublyLinkedList<NodeType>::pushBack(NodeType data)
{
  DoublyNodePtr<NodeType> n;

  // Insert Node After Previous Node
  if (!this->isEmpty())
    // Create New Node and Insert Between Head Previous Node and Head Node
    n = new DoublyNode<NodeType>(data, this->head->prev, this->head);

  // Create n Node and Self-Reference as Previous and Next Node
  else
  {
    n = new DoublyNode<NodeType>(data);
    n->prev = n->next = n;

    // Set n Node as Head
    this->head = n;
  }

  this->increaseLength();
}

// Method to Safely Remove Head Node when it's the Only Node in Circular Doubly Linked List
template <class NodeType>
NodeType CircularDoublyLinkedList<NodeType>::setNULL()
{
  DoublyNodePtr<NodeType> h;

  // Get Head Node and Data
  h = this->head;
  NodeType data = h->data;

  // Set Head as NULL
  this->head = NULL;

  // Deallocate Memory
  delete h;

  this->decreaseLength();

  return data;
}

// Method to Remove Head Node
template <class NodeType>
NodeType CircularDoublyLinkedList<NodeType>::remove()
{
  DoublyNodePtr<NodeType> p, m, n;

  // Check if It's Empty
  if (this->isEmpty())
    return this->error;

  // Circular Doubly Linked List Only have One Node which is Head
  if (this->getLength() == 1)
    return this->setNULL();

  // Get Head Node and Data
  m = this->head;
  NodeType data = m->data;

  // Get Head Previous and Next Node
  p = m->prev;
  n = m->next;

  // Remove m Node from Circular Doubly Linked List
  n->prev = p;
  p->next = n;
  this->head = n;

  // Deallocate Memory
  delete m;

  this->decreaseLength();

  return data;
}

// Method to Remove Node at Head Previous Node
template <class NodeType>
NodeType CircularDoublyLinkedList<NodeType>::pop()
{
  // Check if It's Empty
  if (this->isEmpty())
    return this->error;

  // Circular Doubly Linked List Only have One Node which is Head
  if (this->getLength() == 1)
    return this->setNULL();

  DoublyNodePtr<NodeType> t, p;

  // Set Head Previous Node as Tail. Get Tail Data;
  t = this->head->prev;
  NodeType data = t->data;

  // Get Tail Previous Node
  p = t->prev;

  // Set Tail Previous Next Node to Head
  p->next = this->head;

  // Set Tail Previous Node as Head Previous Node
  this->head->prev = p;

  // Deallocate Memory
  delete t;

  this->decreaseLength();

  return data;
}

// Method to Remove Node at Given Index
template <class NodeType>
NodeType CircularDoublyLinkedList<NodeType>::removeAt(int pos)
{
  int posRemainder = pos % this->length;

  if (posRemainder == 0)
    return this->remove(); // Remove Node at Head

  if ((pos > 0 && posRemainder == this->length - 1) || (pos < 0 && posRemainder == -1))
    return this->pop(); // Remove Tail

  DoublyNodePtr<NodeType> p, m, n;

  // Move from Head Node to Next Node pos-1 Times. Get to Previous Node to the One to be Removed
  p = this->move(pos - 1);

  // Get Node and Data to Remove
  m = p->next;
  NodeType data = m->data;

  // Remove Node
  n = m->next;
  p->next = n;
  n->prev = p;

  // Deallocate Memory
  delete m;

  this->decreaseLength();

  return data;
}

// Method to Modify Node Value at Given Position
template <class NodeType>
NodeType CircularDoublyLinkedList<NodeType>::change(NodeType data, int pos)
{
  // Check if It's Empty
  if (this->isEmpty())
    return this->error; // Node not Found

  // Move to Node
  DoublyNodePtr<NodeType> m = this->move(pos);

  // Get Old Value
  NodeType old = m->data;

  // Assign New Value
  m->data = data;

  return old;
}

// Method to Get Node at Given Position
template <class NodeType>
NodeType CircularDoublyLinkedList<NodeType>::get(int pos)
{
  int posRemainder = pos % this->length;

  // Check if It's Empty
  if (this->isEmpty())
    return this->error; // Node not Found

  // Check pos
  if (posRemainder == 0)
    return this->head->data; // Get Head Node Data

  if ((pos > 0 && posRemainder == this->length - 1) || (pos < 0 && posRemainder == -1))
    return this->head->prev->data; // Get Head Previous Node Data

  // Move to Node
  DoublyNodePtr<NodeType> m = this->move(pos);

  // pos is Out of Range
  if (m == NULL)
    return this->error;

  // Return Value
  return m->data;
}

// Method to Concat Two Circular Doubly Linked Lists
template <class NodeType>
void CircularDoublyLinkedList<NodeType>::concat(CircularDoublyLinkedList<NodeType> *l)
{
  // Check if l is Empty
  if (l->isEmpty())
    return;

  // Assign l First Node Next to this Circular Doubly Linked List Head Previous Node
  this->head->prev->next = l->head;
  l->head->prev = this->head->prev;

  // Save New Head Previous Node
  this->head->prev = l->head->prev;

  // Save New Length
  this->increaseLength(l->getLength());

  // Set l Head to NULL
  l->head = NULL;

  // Set l Length to 0
  l->empty();
}

#endif