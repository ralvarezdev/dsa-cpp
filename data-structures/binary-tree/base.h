#include <cstdlib>
#include <iostream>

#include "../nodes/binNode.h"

using std::cout;

#ifndef BIN_TREE
#define BIN_TREE

// BinNodePtr Definition
template <class NodeType>
using BinNodePtr = BinNode<NodeType> *;

// BINARY TREE CLASS

template <class NodeType>
class BinaryTree
{
protected:
  BinNodePtr<NodeType> root = NULL;

  NodeType error;

  // Protected Methods
  void preorder(BinNodePtr<NodeType>);
  void inorder(BinNodePtr<NodeType>);
  void postorder(BinNodePtr<NodeType>);

public:
  // Public Methods
  void preorder() { preorder(root); };
  void inorder() { inorder(root); };
  void postorder() { postorder(root); };
};

// Method to Print Nodes through Preorder
template <class NodeType>
void BinaryTree<NodeType>::preorder(BinNodePtr<NodeType> p)
{
  static int iter = 0;

  if (iter == 0)
    cout << "\nPreorder\n";

  if (p == NULL)
    return;

  cout << p->data << '\n';
  this->preorder(p->lChild);
  this->preorder(p->rChild);

  iter++;
}

// Method to Print Nodes through Inorder
template <class NodeType>
void BinaryTree<NodeType>::inorder(BinNodePtr<NodeType> p)
{
  static int iter = 0;

  if (iter == 0)
    cout << "\nInorder\n";

  if (p == NULL)
    return;

  this->inorder(p->lChild);
  cout << p->data << '\n';
  this->inorder(p->rChild);

  iter++;
}

// Method to Print Nodes thorugh Postorder
template <class NodeType>
void BinaryTree<NodeType>::postorder(BinNodePtr<NodeType> p)
{
  static int iter = 0;

  if (iter == 0)
    cout << "\nPostorder\n";

  if (p == NULL)
    return;

  this->postorder(p->lChild);
  this->postorder(p->rChild);
  cout << p->data << '\n';

  iter++;
}

#endif
