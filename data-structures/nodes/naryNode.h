#ifndef NARY_NODE
#define NARY_NODE

// N-ARY NODE CLASS
// Self-Referential Structure

template <class NodeType>
class NaryNode
{
public:
  NodeType data;
  NaryNode *firstChild = NULL;
  NaryNode *nextSibling = NULL;

  // Constructors
  NaryNode();
  NaryNode(NodeType);
};

// Node Class Constructors
template <class NodeType>
NaryNode<NodeType>::NaryNode()
{
  return;
}

template <class NodeType>
NaryNode<NodeType>::NaryNode(NodeType data)
{
  this->data = data;
}

#endif