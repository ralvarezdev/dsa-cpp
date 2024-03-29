#include "base.h"
#include "../stack/base.h"

#ifndef NUMBER_BIN_SEARCH_TREE
#define NUMBER_BIN_SEARCH_TREE

// BINARY SEARCH TREE CLASS

template <class NodeType>
class NumberBinarySearchTree : public BinarySearchTree<NodeType>
{
protected:
  // Protected Methods
  bool search(BinNodePtr<NodeType>, NodeType);
  BinNodePtr<NodeType> remove(BinNodePtr<NodeType>, NodeType);
  BinNodePtr<NodeType> getInorderPredecessor(BinNodePtr<NodeType>);
  BinNodePtr<NodeType> getInorderSuccessor(BinNodePtr<NodeType>);

public:
  // Constructors
  NumberBinarySearchTree(NodeType[], int, NodeType);
  NumberBinarySearchTree(QueueLinkedList<NodeType> *, NodeType);
  // ~DoublyLinkedList();

  // Public Methods
  bool search(NodeType key) { return search(this->root, key); };
  void insert(NodeType);
  void remove(NodeType key){remove(this->root, key)};
};

// Binary Search Tree Constructors

// Add Nodes through its Preorder Array Representation
template <class NodeType>
NumberBinarySearchTree<NodeType>::NumberBinarySearchTree(NodeType preArray[], int length, NodeType error)
{
  BinNodePtr<NodeType> p, t;
  int i = 0;

  // Initialize Stack Linked List
  StackLinkedList<BinNodePtr<NodeType>> *stack = new StackLinkedList<BinNodePtr<NodeType>>(NULL);

  // Default Error Value
  this->error = error;

  // Create New Node and Set It as Root
  this->root = new BinNode<NodeType>(preArray[i++]);
  p = this->root;

  // Insert Nodes
  while (i < length)
  {
    // Insert New Node as p Left Child
    if (preArray[i] < p->data)
    {
      // Create New Node
      t = new BinNode<NodeType>(preArray[i++]);

      // Set t as p's Left Child
      p->lChild = t;

      // Push p Node to Stack
      stack->push(p);
    }

    // Insert New Node as p Right Child
    else if (!stack->isEmpty() && preArray[i] > p->data && preArray[i] < stack->top()->data)
    {
      // Create New Node
      t = new BinNode<NodeType>(preArray[i++]);

      // Set t as p's Right Child and Set It as p
      p->rChild = t;
      p = t;
    }

    // Pop Top Node from Stack and Set It as p
    else
      p = stack->pop();
  }
}

// Add Nodes through its Preorder Queue Linked List Representation
template <class NodeType>
NumberBinarySearchTree<NodeType>::NumberBinarySearchTree(QueueLinkedList<NodeType> *preQueue, NodeType error)
{
  BinNodePtr<NodeType> p, t;

  // Check Queue Length
  if (preQueue->getLength() == 0)
    return;

  // Initialize Stack Linked List
  StackLinkedList<BinNodePtr<NodeType>> *stack = new StackLinkedList<BinNodePtr<NodeType>>(NULL);

  // Default Error Value
  this->error = error;

  // Create New Node and Set It as Root
  this->root = new BinNode<NodeType>(preQueue->pop());
  p = this->root;

  // Insert Nodes
  while (preQueue->getLength() != 0)
  {
    // Insert New Node as p Left Child
    if (preQueue->first() < p->data)
    {
      // Create New Node
      t = new BinNode<NodeType>(preQueue->pop());

      // Set t as p's Left Child
      p->lChild = t;

      // Push p Node to Stack
      stack->push(p);
    }

    // Insert New Node as p Right Child
    else if (!stack->isEmpty() && preQueue->first() > p->data && preQueue->first() < stack->top()->data)
    {
      // Create New Node
      t = new BinNode<NodeType>(preQueue->pop());

      // Set t as p's Right Child and Set It as p
      p->rChild = t;
      p = t;
    }

    // Pop Top Node from Stack and Set It as p
    else
      p = stack->pop();
  }
}

// Method to Search Given Key in Binary Search Tree
template <class NodeType>
bool NumberBinarySearchTree<NodeType>::search(BinNodePtr<NodeType> p, NodeType key)
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
void NumberBinarySearchTree<NodeType>::insert(NodeType data)
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

// Recursive Method to Remove Key from Binary Search Tree
template <class NodeType>
BinNodePtr<NodeType> NumberBinarySearchTree<NodeType>::remove(BinNodePtr<NodeType> p, NodeType key)
{
  BinNodePtr<NodeType> q;

  // Check if It's NULL
  if (p == NULL)
    return NULL;

  if (p->lChild == NULL && p->rChild == NULL)
  {
    if (p == this->root)
      this->root = NULL;

    delete p;

    return NULL;
  }

  // Check p's Left Child
  if (key < p->data)
    p->lChild = this->remove(p->lChild, key);

  // Check p's Right Child
  else if (key > p->data)
    p->rChild = this->remove(p->rChild, key);

  // Key is Equal to p's Data
  else
  {
    // Move Inorder Predecessors Up
    if (this->getHeight(p->lChild) > this->getHeight(p->rChild))
    {
      q = this->getInorderPredecessor(p->lChild);
      p->data = q->data;
      p->lChild = this->remove(p->lChild, q->data);
    }

    // Move Inorder Successors Up
    else
    {
      q = this->getInorderSuccessor(p->rChild);
      p->data = q->data;
      p->rChild = this->remove(p->rChild, q->data);
    }
  }

  return p;
}

#endif