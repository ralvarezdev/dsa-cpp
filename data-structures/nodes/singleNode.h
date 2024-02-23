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

  // Set Before Next Node
  this->next = next;
}

template <class NodeType>
SingleNode<NodeType>::SingleNode(NodeType data, SingleNode<NodeType> *prev, SingleNode<NodeType> *next)
{
  this->data = data;

  // Set Between prev and next Nodes
  this->next = next;

  if (prev != NULL)
    prev->next = this;
}

#endif