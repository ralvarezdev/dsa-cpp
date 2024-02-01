#include <cstdlib>

#ifndef LINKED_LISTS
#define LINKED_LISTS

// NODE CLASS
// Self-Referential Structure

template <class T>
class Node
{
public:
  T data;
  Node *next = NULL;

  // Constructors
  Node();
  Node(T);
  Node(T, Node *);
};

// NodePtr Definition
template <class T>
using NodePtr = Node<T> *;

// LINKED LIST CLASS

template <class T>
class LinkedList
{
protected:
  NodePtr<T> head;
  NodePtr<T> tail;
  NodePtr<T> curr;

  int length = 0;

  // Private Methods
  void increaseLength();
  void increaseLength(int);
  void decreaseLength();
  NodePtr<T> move(NodePtr<T>, int);

public:
  // Constructors
  LinkedList();
  LinkedList(T);
  LinkedList(T[], int);
  ~LinkedList();

  // Public Methods
  bool isEmpty();
  void insert(T);
  void push_back(T);
  void insertAt(T, int);
  T remove();
  T pop();
  T removeAt(int);
  T change(T, int);
  T get(int);
  void setCurrent(NodePtr<T>);
  void setCurrent();
  // int count(NodePtr<T>);
  int getLength();
};

// Node Class Constructors
template <class T>
Node<T>::Node()
{
  return;
}

template <class T>
Node<T>::Node(T data)
{
  this->data = data;
}

template <class T>
Node<T>::Node(T data, Node<T> *next)
{
  this->data = data;
  this->next = next;
}

// LINKED LIST CLASS

// Linked List Constructors

// Add Head with Next Node as NULL
template <class T>
LinkedList<T>::LinkedList()
{
  NodePtr<T> p;

  // Add Node as Head and Tail
  this->head = this->tail = p = new Node<T>();

  // Set Head as Current Node
  this->setCurrent();
}

// Add Head with Only One Next Node
template <class T>
LinkedList<T>::LinkedList(T data)
{
  NodePtr<T> p;

  // Add Head
  this->head = p = new Node<T>();

  // Add Next Node
  p = new Node<T>(data);

  // Add Node as Head Next Node and as Tail
  this->tail = this->head->next = p;

  // Increase Length
  this->increaseLength();

  // Set Head as Current Node
  this->setCurrent();
}

// Add Head and Multiple Next Nodes
template <class T>
LinkedList<T>::LinkedList(T data[], int length)
{
  NodePtr<T> p;

  // Add Head
  this->head = p = new Node<T>();

  // Add Node to Head and Set Head as Current Node
  this->curr = this->head;

  // Add Next Nodes
  for (int i = 0; i < length; i++)
  {
    // Add Node
    this->curr->next = p = new Node<T>(data[i]);

    // Set as Current Node
    this->curr = this->curr->next;
  }

  // Set p Node as Tail
  this->tail = p;

  // Increase Length
  this->increaseLength(length);

  // Set Head as Current Node
  this->setCurrent();
}

// Destructor
template <class T>
LinkedList<T>::~LinkedList()
{
  // Remove Node Next to Head if It isn't Empty
  while (!isEmpty())
    this->remove();

  // Remove Head Node
  NodePtr<T> temp = this->head;
  this->head = NULL;

  delete[] temp;
}

// Method to Move to Next Node N Times
template <class T>
NodePtr<T> LinkedList<T>::move(NodePtr<T> p, int n)
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
template <class T>
void LinkedList<T>::insert(T data)
{
  NodePtr<T> n, p;

  // Get Node Next to Head
  n = this->head->next;
  p = new Node<T>(data, n);

  // Set Node Next to Head
  this->head->next = p;

  this->increaseLength();
}

// Method to Insert Node at Given Position
template <class T>
void LinkedList<T>::insertAt(T data, int pos)
{
  // Check pos
  if (pos == 0)
  {
    this->insert(data); // Insert Node Next to Head
    return;
  }

  if (pos < 0)
    pos = this->length + pos + 1; // Get Position

  if (pos >= this->length)
  {
    this->push_back(data); // Insert Node at Tail
    return;
  }

  NodePtr<T> m, q, p;

  // Get Head
  m = this->head;

  // Move to Next Node pos Times
  m = this->move(m, pos);

  // pos is Out of Range
  if (m == NULL)
    return;

  // Perform Last Node Move
  p = m;
  m = m->next;

  // Create New Node and Set m as Next Node
  q = new Node<T>(data, m);

  // Set Node at Given Position
  p->next = q;

  this->increaseLength();
}

// Method to Insert Node at Tail
template <class T>
void LinkedList<T>::push_back(T data)
{
  NodePtr<T> p = new Node<T>(data);

  // Set Node at Tail
  this->tail->next = p;

  // Set Tail
  this->tail = p;

  this->increaseLength();
}

// Method to Remove Node Next to Head
template <class T>
T LinkedList<T>::remove()
{
  if (this->isEmpty())
    return -1;

  // Get Node Next to Head
  NodePtr<T> n = this->head->next;
  T data = n->data;

  // Remove n Node from Linked List
  head->next = n->next;

  // Deallocate Memory
  delete[] n;

  decreaseLength();

  return data;
}

// Method to Remove Node at Tail
template <class T>
T LinkedList<T>::pop()
{
  if (this->isEmpty())
    return -1;

  NodePtr<T> t, p;

  this->decreaseLength();

  // Move to Tail Previous Node
  p = this->move(this->head, this->length);

  // Get Tail
  t = p->next;
  int data = t->data;
  p->next = NULL;

  // Set Previous Node as Tail
  this->tail = p;

  // Deallocate Memory
  delete[] t;

  return data;
}

// Method to Remove Node at Given Index
template <class T>
T LinkedList<T>::removeAt(int pos)
{
  // Check pos
  if (pos == 0)
    return this->remove(); // Remove Node Next to Head

  if (pos < 0)
    pos = this->length + pos; // Get Position

  if (pos > this->length)
    return -1; // Node not Found

  if (pos == this->length)
    return this->pop(); // Remove Tail

  NodePtr<T> m, p, q;

  this->decreaseLength();

  // Move to Next Node pos Times
  m = this->move(this->head, pos);

  // pos is Out of Range
  if (m == NULL)
    return -1;

  // Perform Last Node Move
  p = m;
  m = m->next;

  // Remove Node
  q = m->next;
  T data = m->data;
  p->next = q;

  // Deallocate Memory
  delete[] m;

  return data;
}

// Method to Modify Node Value at Given Position
template <class T>
T LinkedList<T>::change(T data, int pos)
{
  NodePtr<T> n;
  T old;

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
    return -1; // Node not Found

  if (pos == this->length)
  {
    old = this->tail->data;
    this->tail->data = data; // Change Value to Tail
    return old;
  }

  if (this->isEmpty())
    return -1;

  // Set Head to n
  n = this->head;

  // Move to Node
  n = this->move(n, pos);

  // pos is Out of Range
  if (n == NULL)
    return -1;

  // Assign New Value
  old = n->data;
  n->data = data;

  return data;
}

// Method to Get Node at Given Position
template <class T>
T LinkedList<T>::get(int pos)
{
  // Check pos
  if (pos == 0)
    return this->head->next->data; // Get Node Next to Head

  if (pos < 0)
    pos = this->length + pos; // Get Position
  pos += 1;

  if (pos > this->length)
    return -1; // Node not Found

  if (pos == this->length)
    return this->tail->data; // Get Tail

  if (this->isEmpty())
    return -1;

  NodePtr<T> n;

  n = this->head;

  // Move to Node
  n = this->move(n, pos);

  // pos is Out of Range
  if (n == NULL)
    return -1;

  // Return Value
  return n->data;
}

// Method to Check if Linked List is Empty
template <class T>
bool LinkedList<T>::isEmpty()
{
  return this->head->next == NULL;
}

// Method to Increase Linked List Length
template <class T>
void LinkedList<T>::increaseLength()
{
  this->length += 1;
}

template <class T>
void LinkedList<T>::increaseLength(int length)
{
  this->length += length;
}

// Method to Decrease Linked List Length
template <class T>
void LinkedList<T>::decreaseLength()
{
  this->length -= 1;
}

// Method to Set Current Node
template <class T>
void LinkedList<T>::setCurrent(NodePtr<T> p)
{
  this->curr = p;
}

// Method Overload to Set Head Node as Current Node
template <class T>
void LinkedList<T>::setCurrent()
{
  this->curr = this->head;
}

/*
// Count Nodes with a Recursive Method
template <class T>
int LinkedList<T>::count(NodePtr<T> p)
{
  if (p != NULL)
    return count(p->next) + 1;

  // Set Head Node as Current Node
  this->setCurrent();

  return 0;
}
*/

// Method to Get Linked List Length
template <class T>
int LinkedList<T>::getLength()
{
  return this->length;
}

#endif