#include <cstdlib>
#include <math.h>

#include "../nodes/doublyNode.h"
#include "../single-linked-lists/base.h"

using std::abs;

#ifndef DOUBLY_LINKED_LISTS
#define DOUBLY_LINKED_LISTS

// DoublyNodePtr Definition
template <class NodeType>
using DoublyNodePtr = DoublyNode<NodeType> *;

// DOUBLY LINKED LIST CLASS

template <class NodeType>
class DoublyLinkedList
{
protected:
  DoublyNodePtr<NodeType> head = NULL;
  DoublyNodePtr<NodeType> tail = NULL;

  int length = 0;
  NodeType error;

  // Protected Methods
  void increaseLength(int length) { this->length += length; };
  void increaseLength() { this->increaseLength(1); };
  void decreaseLength() { this->increaseLength(-1); };
  void empty() { this->length = 0; };

  DoublyNodePtr<NodeType> move(int);
  NodeType remove(bool);
  NodeType pop(bool);
  NodeType setNULL(bool);

public:
  // Constructors
  DoublyLinkedList(NodeType);
  DoublyLinkedList(NodeType, NodeType);
  DoublyLinkedList(NodeType[], int, NodeType);
  DoublyLinkedList(SingleLinkedList<NodeType>, NodeType);
  ~DoublyLinkedList();

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
  void concat(DoublyLinkedList *);
};

// Doubly Linked List Constructors

// Create Doubly Linked List and Set Error Value
template <class NodeType>
DoublyLinkedList<NodeType>::DoublyLinkedList(NodeType error)
{
  // Default Error Value
  this->error = error;
}

// Add Head with Only One Next Node
template <class NodeType>
DoublyLinkedList<NodeType>::DoublyLinkedList(NodeType data, NodeType error)
{
  DoublyNodePtr<NodeType> p;

  // Default Error Value
  this->error = error;

  // Create New Node
  p = new DoublyNode<NodeType>(data);

  // Set Node as Head and as Tail
  this->tail = this->head = p;

  // Increase Length
  this->increaseLength();
}

// Add Head and Multiple Next Nodes through an Array
template <class NodeType>
DoublyLinkedList<NodeType>::DoublyLinkedList(NodeType data[], int length, NodeType error)
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

  // Set p Node as Tail
  this->tail = p;

  // Increase Length
  this->increaseLength(length);
}

// Add Head and Multiple Next Nodes through a Single Linked List
template <class NodeType>
DoublyLinkedList<NodeType>::DoublyLinkedList(SingleLinkedList<NodeType> list, NodeType error)
{
  DoublyNodePtr<NodeType> p;
  int length = list.getLength();

  // Default Error Value
  this->error = error;

  // Create First Node
  p = new DoublyNode<NodeType>(list.get(0));

  // Set p Node as Head
  this->head = p;

  // Add Next Nodes
  for (int i = 1; i < length; i++)
    // Add Node
    p = new DoublyNode<NodeType>(list.get(i), p);

  // Set p Node as Tail
  this->tail = p;

  // Increase Length
  this->increaseLength(length);
}

// Destructor
template <class NodeType>
DoublyLinkedList<NodeType>::~DoublyLinkedList()
{
  // Remove Tail Node if Doubly Linked List isn't Empty
  while (!isEmpty())
    this->pop(true);
}

// Method to Move to Next Node N Times
template <class NodeType>
DoublyNodePtr<NodeType> DoublyLinkedList<NodeType>::move(int n)
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

  // Move from Tail to Head, or from Head to Tail
  p = backwards ? this->tail : this->head;

  if (backwards)
    // Move to Previous N Nodes
    for (int i = 0; i < mov; i++)
    {
      // Check if Previous Node is NULL
      if (p->prev == NULL)
        return NULL;

      p = p->prev;
    }
  else
    // Move to Next N Nodes
    for (int i = 0; i < mov; i++)
    {
      // Check if Next Node is NULL
      if (p->next == NULL)
        return NULL;

      p = p->next;
    }
  return p;
}

// Method to Insert Node Before Head
template <class NodeType>
void DoublyLinkedList<NodeType>::push(NodeType data)
{
  // Insert Node Before Head
  DoublyNodePtr<NodeType> h = new DoublyNode<NodeType>(data, NULL, this->head);

  // Set h Node as Head
  this->head = h;

  // Set Tail if it's NULL
  if (this->tail == NULL)
    this->tail = this->head;

  this->increaseLength();
}

// Method to Insert Node at Given Position
template <class NodeType>
void DoublyLinkedList<NodeType>::insertAt(NodeType data, int pos)
{
  // Check pos
  if (this->isEmpty() || pos > this->length || abs(pos) > this->length + 1)
    return; // pos Out of Range

  if (pos == 0 || abs(pos) == this->length + 1)
  {
    this->push(data); // Insert Node at Head
    return;
  }

  if (pos == this->length || pos == -1)
  {
    this->pushBack(data); // Insert Node at Tail
    return;
  }

  if (pos > 0)
    pos -= 1;

  DoublyNodePtr<NodeType> p, n;

  // Move to Next or Previous Node pos Times
  p = this->move(pos);

  // pos is Out of Range
  if (p == NULL)
    return;

  // Get Next Node
  n = p->next;

  // Create New Node Between p and n Node
  new DoublyNode<NodeType>(data, p, n);

  this->increaseLength();
}

// Method to Insert Node at Tail
template <class NodeType>
void DoublyLinkedList<NodeType>::pushBack(NodeType data)
{
  // Create New Node and Assign Old Tail as Previous Node
  DoublyNodePtr<NodeType> n = new DoublyNode<NodeType>(data, this->tail);

  // Set Tail
  this->tail = n;

  // Set Head if it's NULL
  if (this->head == NULL)
    this->head = this->tail;

  this->increaseLength();
}

// Method to Safely Remove Node that is Both Head and Tail
template <class NodeType>
NodeType DoublyLinkedList<NodeType>::setNULL(bool destructor)
{
  DoublyNodePtr<NodeType> t, h;

  // Get Head and Tail Node and Data
  h = this->head;
  t = this->tail;
  NodeType data = h->data;

  // Set Head and Tail Node as NULL
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
NodeType DoublyLinkedList<NodeType>::remove(bool destructor)
{
  // Check if It's Empty
  if (this->isEmpty())
    return this->error;

  // Head and Tail Node are the Same
  if (this->getLength() == 1)
    return this->setNULL(destructor);

  DoublyNodePtr<NodeType> m, n;

  // Get Head Node and Data
  m = this->head;
  NodeType data = m->data;

  // Get Head Next Node
  n = m->next;

  // Remove m Node from Doubly Linked List
  this->head = n;
  n->prev = NULL;

  // Deallocate Memory
  if (destructor)
    delete[] m;
  else
    delete m;

  decreaseLength();

  return data;
}

// Method to Remove Node at Tail
template <class NodeType>
NodeType DoublyLinkedList<NodeType>::pop(bool destructor)
{
  // Check if It's Empty
  if (this->isEmpty())
    return this->error;

  // Head and Tail Node are the Same
  if (this->getLength() == 1)
    return this->setNULL(destructor);

  DoublyNodePtr<NodeType> t, p;

  // Get Tail Node and Data
  t = this->tail;
  NodeType data = t->data;

  // Get Tail Previous Node
  p = this->tail->prev;

  // Remove Tail Node
  p->next = NULL;

  // Set Previous Node as Tail
  this->tail = p;

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
NodeType DoublyLinkedList<NodeType>::removeAt(int pos)
{
  // Check if It's Empty and Check pos
  if (this->isEmpty() || pos >= this->length || abs(pos) >= this->length + 1)
    return this->error; // Node not Found

  if (pos == 0 || pos == -1 * this->length)
    return this->remove(); // Remove Node at Head

  if (pos == -1 || pos == this->length - 1)
    return this->pop(); // Remove Tail

  DoublyNodePtr<NodeType> p, m, n;

  // Move from Head Node to Next Node pos-1 Times. Get to Previous Node to the One to be Removed
  p = this->move(pos - 1);

  // pos is Out of Range
  if (p == NULL)
    return this->error;

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
NodeType DoublyLinkedList<NodeType>::change(NodeType data, int pos)
{
  // Check if It's Empty and Check pos
  if (this->isEmpty() || pos >= this->length || abs(pos) >= this->length + 1)
    return this->error; // Node not Found

  // Move to Node
  DoublyNodePtr<NodeType> m = this->move(pos);

  // pos is Out of Range
  if (m == NULL)
    return this->error;

  // Get Old Value
  NodeType old = m->data;

  // Assign New Value
  m->data = data;

  return old;
}

// Method to Get Node at Given Position
template <class NodeType>
NodeType DoublyLinkedList<NodeType>::get(int pos)
{
  // Check if It's Empty and Check pos
  if (this->isEmpty() || pos >= this->length || abs(pos) >= length + 1)
    return this->error; // Node not Found

  if (pos == 0 || pos == -1 * length)
    return this->head->data; // Get Head Node Data

  if (pos == -1 || pos == this->length - 1)
    return this->tail->data; // Get Tail Node Data

  // Move to Node
  DoublyNodePtr<NodeType> m = this->move(pos);

  // pos is Out of Range
  if (m == NULL)
    return this->error;

  // Return Value
  return m->data;
}

// Method to Concat Two Doubly Linked Lists
template <class NodeType>
void DoublyLinkedList<NodeType>::concat(DoublyLinkedList<NodeType> *l)
{
  // Check if l is Empty
  if (l->isEmpty())
    return;

  // Assign l First Node Next to this Doubly Linked List Tail
  this->tail->next = l->head;
  l->head->prev = this->tail;

  // Save New Tail Node
  this->tail = l->tail;

  // Save New Length
  this->increaseLength(l->getLength());

  // Set l Head and Tail Node to NULL
  l->head = l->tail = NULL;

  // Set l Length to 0
  l->empty();
}

#endif