#include "binNode.h"

#ifndef AVL_NODE
#define AVL_NODE

// AVL NODE CLASS
// Self-Referential Structure

template <class NodeType>
class AVLNode : public BinNode<NodeType>
{
public:
  height = 1;

  // Inherit Constructors
  using BinNode<NodeType>::BinNode();

  // Public Methods
  int getNodeHeight();
};

// AVLNodePtr Definition
template <class NodeType>
using AVLNodePtr = AVLNode<NodeType> *;

// Method to Get Node Height
template <class NodeType>
int AVLTree<NodeType>::getNodeHeight(AVLNodePtr<NodeType> p)
{
  int hl, hr;

  // Get Left and Right Child Node Height
  hl = p->lChild != NULL ? p->lChild->height : 0;
  hr = p->rChild != NULL ? p->rChild->height : 0;

  return hl > hr ? hl + 1 : hr + 1;
}

#endif