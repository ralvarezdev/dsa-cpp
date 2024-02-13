#ifndef DOUBLY_NODE
#define DOUBLY_NODE

// DOUBLY NODE CLASS
// Self-Referential Structure

template <class NodeType>
class DoublyNode
{
public:
  NodeType data;
  DoublyNode *prev = NULL;
  DoublyNode *next = NULL;

  // Constructors
  DoublyNode();
  DoublyNode(NodeType);
  DoublyNode(NodeType, DoublyNode *);
  DoublyNode(NodeType, DoublyNode *, DoublyNode *);
};

// Doubly Node Class Constructors
template <class NodeType>
DoublyNode<NodeType>::DoublyNode()
{
  return;
}

template <class NodeType>
DoublyNode<NodeType>::DoublyNode(NodeType data)
{
  this->data = data;
}

template <class NodeType>
DoublyNode<NodeType>::DoublyNode(NodeType data, DoublyNode<NodeType> *prev)
{
  this->data = data;
  this->prev = prev;

  if (prev != NULL)
    prev->next = this;
}

template <class NodeType>
DoublyNode<NodeType>::DoublyNode(NodeType data, DoublyNode<NodeType> *prev, DoublyNode<NodeType> *next)
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