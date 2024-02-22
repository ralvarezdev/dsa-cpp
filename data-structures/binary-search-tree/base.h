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
  // Constructors
  BinarySearchTree(NodeType[], int, NodeType);
  BinarySearchTree(QueueLinkedList<NodeType>, NodeType);
  // ~DoublyLinkedList();

  // Public Methods
  void inorder() { inorder(root); };
  bool search(NodeType key) { return search(root, key); };
  void insert(NodeType);
};

// Binary Search Tree Constructors

// Add Nodes through an Array
template <class NodeType>
BinarySearchTree<NodeType>::BinarySearchTree(NodeType data[], int length, NodeType error)
{
  // Default Error Value
  this->error = error;

  // Create New Node and Set It as Root
  this->root = new BinNode<NodeType>(data[0]);

  // Insert Nodes
  for (int i = 1; i < length; i++)
    // Insert Node
    this->insert(data[i]);
}

// Add Nodes through a Queue Linked list
template <class NodeType>
BinarySearchTree<NodeType>::BinarySearchTree(QueueLinkedList<NodeType> queue, NodeType error)
{
  NodeType data;

  // Default Error Value
  this->error = error;

  // Check Queue Length
  if (queue.getLength() == 0)
    return;

  // Create New Node and Set It as Root
  this->root = new BinNode<NodeType>(queue.dequeue());

  // Insert Nodes while Queue isn't Empty
  while (!queue.isEmpty())
  {
    // Get Node Data from Queue
    data = queue.dequeue();

    // Insert Node to Binary Search Tree
    this->insert(data);
  }
}

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