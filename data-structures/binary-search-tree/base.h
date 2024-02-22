#include "../binary-tree/base.h"

#ifndef BIN_SEARCH_TREE
#define BIN_SEARCH_TREE

// BINARY SEARCH TREE CLASS

template <class NodeType>
class BinarySearchTree : public BinaryTree<NodeType>
{
protected:
  // Protected Methods
  void inorder(BinNodePtr<NodeType>);
  bool search(BinNodePtr<NodeType>, NodeType);

public:
  // Public Methods
  void inorder() { inorder(root); };
  bool search(NodeType) { return search(root, NodeType); };
  void insert(NodeType);
};

// Method to Print Nodes through Inorder Traversal
template <class NodeType>
void BinarySearchTree<NodeType>::inorder(BinNodePtr<NodeType> p)
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

// Method to Search Given Key in Binary Search Tree
template <class NodeType>
bool BinarySearchTree<NodeType>::search(BinNodePtr<NodeType> p, NodeType key)
{
  // Check p Node
  if (p == NULL)
    return false;

  // Compare p Node's Data
  if (key == p->data)
    return true;
  else if (key < p->data)
    return this->search(p->lChild, key);
  else
    return this->search(p->rChild, key);
}

// Method to Insert Data to Binary Search Tree
template <class NodeType>
void BinarySearchTree<NodeType>::insert(NodeType data)
{
  BinNodePtr<NodeType> p, q;

  // Set Root as q Node
  q = this->root;

  // Set p Node as NULL
  p = NULL;

  // Check q Node
  while (q->NULL)
  {
    p = q;

    // Data Already Inserted
    if (data == q->data)
      return;

    // Check at Left Child
    else if (data < q->data)
      q = q->lChild;

    // Check at Right Child
    else
      q = q->rChild;
  }

  // Create New Node
  p = new BinNode<NodeType>(data);

  // Assign p Node as Child to q Node
  if (data < q->data)
    q->lChild = p;
  else
    q->rChild = p;
}

#endif