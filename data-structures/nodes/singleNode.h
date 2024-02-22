#ifndef SINGLE_NODE
#define SINGLE_NODE

// SINGLE NODE CLASS
// Self-Referential Structure

template <class NodeType>
class SingleNode
{
public:
  NodeType data;
  SingleNode *next = NULL;

  // Constructors
  SingleNode();
  SingleNode(NodeType);
  SingleNode(NodeType, SingleNode *);
  SingleNode(NodeType, SingleNode *, SingleNode *);
};

// Node Class Constructors
template <class NodeType>
SingleNode<NodeType>::SingleNode()
{
  return;
}

template <class NodeType>
SingleNode<NodeType>::SingleNode(NodeType data)
{
  this->data = data;
}

template <class NodeType>
SingleNode<NodeType>::SingleNode(NodeType data, SingleNode<NodeType> *next)
{
  this->data = data;
  this->next = next;
}

template <class NodeType>
SingleNode<NodeType>::SingleNode(NodeType data, SingleNode<NodeType> *prev, SingleNode<NodeType> *next)
{
  this->data = data;
  prev->next = this;
  this->next = next;
}

#endif