#include "../queue/base.h"
#include "../nodes/binNode.h"

#ifndef BIN_SEARCH_TREE
#define BIN_SEARCH_TREE

// BINARY SEARCH TREE CLASS

template <class NodeType>
class BinarySearchTree
{
protected:
  BinNodePtr<NodeType> root = NULL;
  NodeType error;

  // Protected Methods
  BinNodePtr<NodeType> getInorderPredecessor(BinNodePtr<NodeType>);
  BinNodePtr<NodeType> getInorderSuccessor(BinNodePtr<NodeType>);

  void preorder(BinNodePtr<NodeType> p) { p->preorder(); };
  void inorder(BinNodePtr<NodeType> p) { p->inorder(); };
  void postorder(BinNodePtr<NodeType> p) { p->postorder(); };
  void levelOrder(BinNodePtr<NodeType> p) { p->levelOrder(); };
  int countNodes(BinNodePtr<NodeType> p) { return p->countNodes(); };
  int countTypeNodes(BinNodePtr<NodeType> p, bool countLeafNodes) { return p->countTypeNodes(countLeafNodes); };
  int getHeight(BinNodePtr<NodeType> p) { return p->getHeight(); };

public:
  // Constructors
  BinarySearchTree(){};
  BinarySearchTree(NodeType);
  BinarySearchTree(NodeType, NodeType);

  // Destructor
  virtual ~BinarySearchTree()
  {
    BinNodePtr<NodeType> n, children[2];

    // Initialize Queue that will Store All the Nodes whose Memory will be Deallocated
    QueueLinkedList<BinNodePtr<NodeType>> *nodes = new QueueLinkedList<BinNodePtr<NodeType>>(NULL);

    // Get Root Node
    n = this->root;
    this->root = NULL;
    nodes->push(n);

    while (!nodes->isEmpty())
    {
      // Get First Node
      n = nodes->dequeue();

      // Get n's Children
      children[0] = n->lChild;
      children[1] = n->rChild;

      for (int i = 0; i < 2; i++)
      {
        // Check if the Child Exists
        if (children[i] == NULL)
          continue;

        // Push n's Child
        nodes->enqueue(children[i]);
      }

      // Deallocate Parent Node Data
      delete n;
    }

    // Deallocate Memory
    delete queue;
  }

  // Public Methods
  void preorder() { this->root->preorder(); };
  void inorder() { this->root->inorder(); };
  void postorder() { this->root->postorder(); };
  void levelOrder() { this->root->levelOrder(); };
  int countNodes() { return this->root->countNodes(); };
  int countTypeNodes(bool countLeafNodes) { return this->root->countTypeNodes(countLeafNodes); };
  int getHeight() { return this->root->getHeight(); };
  NodeType getError() { return this->error; };
};

// Binary Search Tree Constructors

// Create Number Binary Search Tree and Set Error Value
template <class NodeType>
BinarySearchTree<NodeType>::BinarySearchTree(NodeType error)
{
  // Default Error Value
  this->error = error;
}

// Add Only Root Node
template <class NodeType>
BinarySearchTree<NodeType>::BinarySearchTree(NodeType data, NodeType error)
{
  // Default Error Value
  this->error = error;

  // Create New Node and Assign It as Root Node
  this->root = new BinNode<NodeType>(data);
}

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