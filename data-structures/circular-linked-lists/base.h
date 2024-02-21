#include <cstdlib>
#include <math.h>

#include "../doubly-linked-lists/base.h"

using std::abs;

#ifndef CIRCULAR_LINKED_LISTS
#define CIRCULAR_LINKED_LISTS

// CIRCULAR LINKED LIST CLASS

template <class NodeType>
class CircularLinkedList
{
protected:
  DoublyNodePtr<NodeType> head = NULL;

  int length = 0;
  NodeType error;

  // Protected Methods
  void increaseLength();
  void increaseLength(int);
  void decreaseLength();
  DoublyNodePtr<NodeType> move(int);
  NodeType remove(bool);
  NodeType pop(bool);
  NodeType setNULL(bool);

public:
  // Constructors
  CircularLinkedList(NodeType);
  CircularLinkedList(NodeType, NodeType);
  CircularLinkedList(NodeType[], int, NodeType);
  ~CircularLinkedList();

  // Public Methods
  NodeType getError();
  bool isEmpty();
  void push(NodeType);
  void pushBack(NodeType);
  void insertAt(NodeType, int);
  NodeType remove() { return remove(false); };
  NodeType pop() { return pop(false); };
  NodeType removeAt(int);
  NodeType change(NodeType, int);
  NodeType get(int);
  int getLength();
  void concat(CircularLinkedList);
};

// Circular Linked List Constructors

// Create Circular Linked List and Set Error Value
template <class NodeType>
CircularLinkedList<NodeType>::CircularLinkedList(NodeType error)
{
  // Default Error Value
  this->error = error;
}

// Add Head with Only One Next Node
template <class NodeType>
CircularLinkedList<NodeType>::CircularLinkedList(NodeType data, NodeType error)
{
  DoublyNodePtr<NodeType> p;

  // Default Error Value
  this->error = error;

  // Create New Node
  p = new DoublyNode<NodeType>(data);

  // Set Node as Head
  this->head = p;

  // Set Head as Head Next Node and as Head Previous Node
  this->head->next = this->head->prev = this->head;

  // Increase Length
  this->increaseLength();
}

// Add Head and Multiple Next Nodes
template <class NodeType>
CircularLinkedList<NodeType>::CircularLinkedList(NodeType data[], int length, NodeType error)
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

// Destructor
template <class NodeType>
CircularLinkedList<NodeType>::~CircularLinkedList()
{
  // Remove Head Previous Node if It isn't Empty
  while (!isEmpty())
    this->pop(true);
}

// Method to Get Error Value
template <class NodeType>
NodeType CircularLinkedList<NodeType>::getError()
{
  return this->error;
}

// Method to Move to Next Node N Times
template <class NodeType>
DoublyNodePtr<NodeType> CircularLinkedList<NodeType>::move(int n)
{
  DoublyNodePtr<NodeType> p;
  int mov = n > 0 ? n : n + 1;
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
void CircularLinkedList<NodeType>::push(NodeType data)
{
  DoublyNodePtr<NodeType> h;

  // Insert Node Before Head
  if (this->isEmpty())
  {
    h = new DoublyNode<NodeType>(data, NULL, NULL);
    h->prev = h->next = h;
  }
  else
    h = new DoublyNode<NodeType>(data, this->head->prev, this->head);

  // Set h Node as Head
  this->head = h;

  this->increaseLength();
}

// Method to Insert Node at Given Position
template <class NodeType>
void CircularLinkedList<NodeType>::insertAt(NodeType data, int pos)
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

  DoublyNodePtr<NodeType> p, n;

  // Move to Next or Prev Node pos Times
  p = this->move(pos);

  // Get Next Node
  n = p->next;

  // Create New Node
  new DoublyNode<NodeType>(data, p, n);

  this->increaseLength();
}

// Method to Insert Node at Head Previous Node
template <class NodeType>
void CircularLinkedList<NodeType>::pushBack(NodeType data)
{
  // Create New Node and Assign Old Head Previous Node as Previous Node
  DoublyNodePtr<NodeType> n = new DoublyNode<NodeType>(data, this->head->prev, this->head);

  // Set Head if it's NULL
  if (this->head == NULL)
  {
    h->prev = h->next = h;
    this->head = h;
  }

  this->increaseLength();
}

// Method to Safely Remove Head Node when it's the Only Node in Linked List
template <class NodeType>
NodeType CircularLinkedList<NodeType>::setNULL(bool destructor)
{
  DoublyNodePtr<NodeType> h;

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
NodeType CircularLinkedList<NodeType>::remove(bool destructor)
{
  DoublyNodePtr<NodeType> m, n;

  if (this->isEmpty())
    return this->error;

  // Linked List Only have One Node which is Head
  if (this->getLength() == 1)
    return this->setNULL(destructor);

  // Get Head Node
  m = this->head;
  NodeType data = m->data;

  // Get Next Node to the One that will be Removed
  n = m->next;

  // Remove m Node from Linked List
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
NodeType CircularLinkedList<NodeType>::pop(bool destructor)
{
  if (this->isEmpty())
    return this->error;

  // Linked List Only have One Node which is Head
  if (this->getLength() == 1)
    return this->setNULL(destructor);

  DoublyNodePtr<NodeType> t, p;

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
NodeType CircularLinkedList<NodeType>::removeAt(int pos)
{
  // Check pos
  if (pos == -1 || pos >= this->length)
    return this->error; // Node not Found

  if (pos == 0)
    return this->remove(); // Remove Node at Head

  if (pos == this->length - 1)
    return this->pop(); // Remove Tail

  pos -= 1;

  DoublyNodePtr<NodeType> p, m, n;

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
NodeType CircularLinkedList<NodeType>::change(NodeType data, int pos)
{
  if (this->isEmpty() || pos >= this->length || abs(pos) >= this->length + 1)
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
NodeType CircularLinkedList<NodeType>::get(int pos)
{
  // Check pos
  if (this->isEmpty() || pos >= this->length || abs(pos) >= this->length + 1)
    return this->error; // Node not Found

  if (pos == 0 || pos == -1 * length)
    return this->head->data; // Get Node Next to Head Data

  if (pos == this->length - 1 || pos == -1)
    return this->head->prev->data; // Get Head Previous Node Data

  // Move to Node
  DoublyNodePtr<NodeType> m = this->move(pos);

  // pos is Out of Range
  if (m == NULL)
    return this->error;

  // Return Value
  return m->data;
}

// Method to Check if Linked List is Empty
template <class NodeType>
bool CircularLinkedList<NodeType>::isEmpty()
{
  return this->head == NULL;
}

// Method to Increase Linked List Length
template <class NodeType>
void CircularLinkedList<NodeType>::increaseLength()
{
  this->length += 1;
}

template <class NodeType>
void CircularLinkedList<NodeType>::increaseLength(int length)
{
  this->length += length;
}

// Method to Decrease Linked List Length
template <class NodeType>
void CircularLinkedList<NodeType>::decreaseLength()
{
  this->length -= 1;
}

// Method to Get Linked List Length
template <class NodeType>
int CircularLinkedList<NodeType>::getLength()
{
  return this->length;
}

// Method to Concat Two Linked Lists
template <class NodeType>
void CircularLinkedList<NodeType>::concat(CircularLinkedList<NodeType> l)
{
  // Assign l First Node Next to this Linked List Head Previous Node
  this->head->prev->next = l->head;
  l->head->prev = this->head->prev;

  // Save New Head Previous Node
  this->head->prev = l->head->prev;

  // Save New Length
  this->increaseLength(l->getLength());
}

#endif