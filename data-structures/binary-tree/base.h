#include <cstdlib>
#include <iostream>

#include "../queue/base.h"
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
  void levelOrder(BinNodePtr<NodeType>);
  int countNodes(BinNodePtr<NodeType>);
  int countTypeNodes(BinNodePtr<NodeType>, bool);
  int getHeight(BinNodePtr<NodeType>);

public:
  // Constructors
  BinaryTree(NodeType);
  BinaryTree(NodeType, NodeType);

  // Public Methods
  void preorder() { preorder(root); };
  void inorder() { inorder(root); };
  void postorder() { postorder(root); };
  void levelOrder() { levelOrder(root); };
  int countNodes() { return countNodes(root); };
  int countLeafNodes() { return countTypeNodes(root, true); };
  int countNonLeafNodes() { return countTypeNodes(root, false); };
  int getHeight() { return getHeight(root); };
};

// Binary Tree Constructors

// Create Binary Tree and Set Error Value
template <class NodeType>
BinaryTree<NodeType>::BinaryTree(NodeType error)
{
  // Default Error Value
  this->error = error;
}

// Add Only Root Node
template <class NodeType>
BinaryTree<NodeType>::BinaryTree(NodeType data, NodeType error)
{
  // Default Error Value
  this->error = error;

  // Create New Node and Set It as Root
  this->root = new BinNode<NodeType>(data);
}

// Method to Print Nodes through Preorder Traversal
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

// Method to Print Nodes through Inorder Traversal
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

// Method to Print Nodes thorugh Postorder Traversal
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

// Method to Print Nodes through Level Order Traversal
template <class NodeType>
void BinaryTree<NodeType>::levelOrder(BinNodePtr<NodeType> p)
{
  QueueLinkedList<NodeType> q = QueueLinkedList<NodeType>(this->error);

  // Print Node Data
  cout << p->data << '\n';

  // Push Node to Queue
  q->push(p);

  while (!q->isEmpty())
  {
    // Get First Node
    p = q->enqueue();

    // Check p's Left Child
    if (p->lChild != NULL)
    {
      // Print Left Child Data
      cout << p->lChild->data << '\n';

      // Push p's Left Child
      q->enqueue(p->lChild);
    }

    // Check p's Right Child
    if (p->rChild != NULL)
    {
      // Print Right Child Data
      cout << p->rChild->data << '\n';

      // Push p's Right Child
      q->enqueue(p->rChild);
    }
  }
}

// Method to Count Nodes
template <class NodeType>
int BinaryTree<NodeType>::countNodes(BinNodePtr<NodeType> p)
{
  int x = 0, y = 0;

  // Check p Node
  if (p == NULL)
    return 0;

  x = this->count(p->lChild);
  y = this->count(p->rChild);
  return x + y + 1;
}

// Method to Count Leaf or Non-Leaf Nodes
template <class NodeType>
int BinaryTree<NodeType>::countTypeNodes(BinNodePtr<NodeType> p, bool countLeafNodes)
{
  int x = 0, y = 0;

  // Check p Node
  if (p != NULL)
  {
    x = this->countLeafNodes(p->lChild);
    y = this->countLeafNodes(p->rChild);

    // Count Leaf Nodes
    if (countLeafNodes)
    {
      if (p->lChild == NULL && p->rChild == NULL)
        return x + y + 1;
    }
    // Count Non-Leaf Nodes
    else if (p->lChild != NULL || p->rChild != NULL)
      return x + y + 1;

    return x + y;
  }
}

// Method to Get Tree Height
template <class NodeType>
int BinaryTree<NodeType>::getHeight(BinNodePtr<NodeType> p)
{
  int x = 0, y = 0;

  // Check p Node
  if (p == NULL)
    return 0;

  x = this->getHeight(p->lChild);
  y = this->getHeight(p->rChild);

  if (x >= y)
    return x + 1;
  return y + 1;
}

#endif
