#ifndef DOUBLY_NODE
#define DOUBLY_NODE

// DOUBLY NODE CLASS
// Self-Referential Structure

template <class T>
class DoublyNode
{
public:
  T data;
  DoublyNode *prev = NULL;
  DoublyNode *next = NULL;

  // Constructors
  DoublyNode();
  DoublyNode(T);
  DoublyNode(T, DoublyNode *);
  DoublyNode(T, DoublyNode *, DoublyNode *);
};

// Doubly Node Class Constructors
template <class T>
DoublyNode<T>::DoublyNode()
{
  return;
}

template <class T>
DoublyNode<T>::DoublyNode(T data)
{
  this->data = data;
}

template <class T>
DoublyNode<T>::DoublyNode(T data, DoublyNode<T> *prev)
{
  this->data = data;
  this->prev = prev;

  if (prev != NULL)
    prev->next = this;
}

template <class T>
DoublyNode<T>::DoublyNode(T data, DoublyNode<T> *prev, DoublyNode<T> *next)
{
  this->data = data;
  this->prev = prev;
  this->next = next;

  if (prev != NULL)
    prev->next = this;
  if (next != NULL)
    next->prev = this;
}

#endif