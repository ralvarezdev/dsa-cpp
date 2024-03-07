#include "../binary-tree/base.h"

#ifndef BIN_SEARCH_TREE
#define BIN_SEARCH_TREE

// BINARY SEARCH TREE CLASS

template <class NodeType>
class BinarySearchTree : public BinaryTree<NodeType>
{
protected:
  // Protected Methods
  BinNodePtr<NodeType> getInorderPredecessor(BinNodePtr<NodeType>);
  BinNodePtr<NodeType> getInorderSuccessor(BinNodePtr<NodeType>);

public:
  // Inherit Constructors
  using BinaryTree<NodeType>::BinaryTree;
};

// Method to Get Inorder Predecessor of Given Node
template <class NodeType>
BinNodePtr<NodeType> BinarySearchTree<NodeType>::getInorderPredecessor(BinNodePtr<NodeType> p)
{
  while (p != NULL && p->rChild != NULL)
    p = p->rChild;

  return p;
}

// Method to Get Inorder Successor of Given Node
template <class NodeType>
BinNodePtr<NodeType> BinarySearchTree<NodeType>::getInorderSuccessor(BinNodePtr<NodeType> p)
{
  while (p != NULL && p->lChild != NULL)
    p = p->lChild;

  return p;
}

#endif