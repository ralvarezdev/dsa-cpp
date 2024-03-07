#include <iostream>

#include "../queue/base.h"

using std::cout;

#ifndef BIN_NODE
#define BIN_NODE

// BINARY NODE CLASS
// Self-Referential Structure

template <class NodeType>
class BinNode
{
protected:
  // Protected Methods
  void preorder(BinNode<NodeType> *);
  void inorder(BinNode<NodeType> *);
  void postorder(BinNode<NodeType> *);
  void levelOrder(BinNode<NodeType> *);
  int countNodes(BinNode<NodeType> *);
  int countTypeNodes(BinNode<NodeType> *, bool);
  int getHeight(BinNode<NodeType> *);

public:
  NodeType data;
  BinNode *lChild = NULL; // Left Child
  BinNode *rChild = NULL; // Right Child

  // Constructors
  BinNode();
  BinNode(NodeType);

  // Public Methods
  void preorder() { this->preorder(this); };
  void inorder() { this->inorder(this); };
  void postorder() { this->postorder(this); };
  void levelOrder() { this->levelOrder(this); };
  int countNodes() { return this->countNodes(this); };
  int countTypeNodes(bool countLeafNodes) { return this->countTypeNodes(this, countLeafNodes); };
  int getHeight() { return this->getHeight(this); };
};

// BinNodePtr Definition
template <class NodeType>
using BinNodePtr = BinNode<NodeType> *;

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

// Method to Print Nodes through Preorder Traversal
template <class NodeType>
void BinNode<NodeType>::preorder(BinNodePtr<NodeType> p)
{
  static int iter = 0;

  if (iter == 0)
    cout << "\nPreorder\n";
  iter++;

  if (p == NULL)
    return;

  cout << p->data << '\n';
  this->preorder(p->lChild);
  this->preorder(p->rChild);
}

// Method to Print Nodes through Inorder Traversal
template <class NodeType>
void BinNode<NodeType>::inorder(BinNodePtr<NodeType> p)
{
  static int iter = 0;

  if (iter == 0)
    cout << "\nInorder\n";
  iter++;

  if (p == NULL)
    return;

  this->inorder(p->lChild);
  cout << p->data << '\n';
  this->inorder(p->rChild);
}

// Method to Print Nodes thorugh Postorder Traversal
template <class NodeType>
void BinNode<NodeType>::postorder(BinNodePtr<NodeType> p)
{
  static int iter = 0;

  if (iter == 0)
    cout << "\nPostorder\n";
  iter++;

  if (p == NULL)
    return;

  this->postorder(p->lChild);
  this->postorder(p->rChild);
  cout << p->data << '\n';
}

// Method to Print Nodes through Level Order Traversal
template <class NodeType>
void BinNode<NodeType>::levelOrder(BinNodePtr<NodeType> p)
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
int BinNode<NodeType>::countNodes(BinNodePtr<NodeType> p)
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
int BinNode<NodeType>::countTypeNodes(BinNodePtr<NodeType> p, bool countLeafNodes)
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
int BinNode<NodeType>::getHeight(BinNodePtr<NodeType> p)
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