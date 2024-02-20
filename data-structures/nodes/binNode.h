#ifndef BIN_NODE
#define BIN_NODE

// SINGLE NODE CLASS
// Self-Referential Structure

template <class NodeType>
class BinNode
{
public:
  NodeType data;
  BinNode *lChild = NULL; // Left Child
  BinNode *rChild = NULL; // Right Child

  // Constructors
  BinNode();
  BinNode(NodeType);
};

// Node Class Constructors
template <class NodeType>
BinNode<NodeType>::BinNode()
{
  return;
}

template <class NodeType>
BinNode<NodeType>::BinNode(NodeType data)
{
  this->data = data;
}

#endif