#ifndef SINGLE_NODE
#define SINGLE_NODE

// SINGLE NODE CLASS
// Self-Referential Structure

template <class T>
class SingleNode
{
public:
  T data;
  SingleNode *next = NULL;

  // Constructors
  SingleNode();
  SingleNode(T);
  SingleNode(T, SingleNode *);
};

// Node Class Constructors
template <class T>
SingleNode<T>::SingleNode()
{
  return;
}

template <class T>
SingleNode<T>::SingleNode(T data)
{
  this->data = data;
}

template <class T>
SingleNode<T>::SingleNode(T data, SingleNode<T> *next)
{
  this->data = data;
  this->next = next;
}

#endif