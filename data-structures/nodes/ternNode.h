#ifndef TERN_NODE
#define TERN_NODE

// TERNARY NODE CLASS
// Self-Referential Structure

template <class NodeType>
class TernNode
{
protected:
  // Protected Methods
  void preorder(TernNode<NodeType> *);
  void inorder(TernNode<NodeType> *);
  void postorder(TernNode<NodeType> *);
  void levelOrder(TernNode<NodeType> *);
  int countNodes(TernNode<NodeType> *);
  int countTypeNodes(TernNode<NodeType> *, bool);
  int getHeight(TernNode<NodeType> *);

public:
  NodeType data;
  TernNode *lChild = NULL; // Left Child
  TernNode *mChild = NULL; // Mid Child
  TernNode *rChild = NULL; // Right Child

  // Constructors
  TernNode();
  TernNode(NodeType);

  // Public Methods
  void preorder() { this->preorder(this); };
  void postorder() { this->postorder(this); };
  void levelOrder() { this->levelOrder(this); };
  int countNodes() { this->countNodes(this); };
  int countTypeNodes(bool countLeafNodes) { this->countTypeNodes(this, countLeafNodes); };
  int getHeight() { this->getHeight(this); };
};

// TernNodePtr Definition
template <class NodeType>
using TernNodePtr = TernNode<NodeType> *;

// Node Class Constructors
template <class NodeType>
TernNode<NodeType>::TernNode()
{
  return;
}

template <class NodeType>
TernNode<NodeType>::TernNode(NodeType data)
{
  this->data = data;
}

// Method to Print Nodes through Preorder Traversal
template <class NodeType>
void TernNode<NodeType>::preorder(TernNodePtr<NodeType> p)
{
  static int iter = 0;

  if (iter == 0)
    cout << "\nPreorder\n";

  if (p == NULL)
    return;

  cout << p->data << '\n';
  this->preorder(p->lChild);
  this->preorder(p->mChild);
  this->preorder(p->rChild);

  iter++;
}

// Method to Print Nodes thorugh Postorder Traversal
template <class NodeType>
void TernNode<NodeType>::postorder(TernNodePtr<NodeType> p)
{
  static int iter = 0;

  if (iter == 0)
    cout << "\nPostorder\n";

  if (p == NULL)
    return;

  this->postorder(p->lChild);
  this->postorder(p->mChild);
  this->postorder(p->rChild);
  cout << p->data << '\n';

  iter++;
}

// Method to Print Nodes through Level Order Traversal
template <class NodeType>
void TernNode<NodeType>::levelOrder(TernNodePtr<NodeType> p)
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

    // Check p's Mid Child
    if (p->mChild != NULL)
    {
      // Print Mid Child Data
      cout << p->mChild->data << '\n';

      // Push p's Mid Child
      q->enqueue(p->mChild);
    }
  }
}

// Method to Count Nodes
template <class NodeType>
int TernNode<NodeType>::countNodes(TernNodePtr<NodeType> p)
{
  int x = 0, y = 0, z = 0;

  // Check p Node
  if (p == NULL)
    return 0;

  x = this->count(p->lChild);
  y = this->count(p->mChild);
  z = this->count(p->rChild);

  return x + y + z + 1;
}

// Method to Count Leaf or Non-Leaf Nodes
template <class NodeType>
int TernNode<NodeType>::countTypeNodes(TernNodePtr<NodeType> p, bool countLeafNodes)
{
  int x = 0, y = 0, z = 0;

  // Check p Node
  if (p != NULL)
  {
    x = this->countLeafNodes(p->lChild);
    y = this->countLeafNodes(p->mChild);
    z = this->countLeafNodes(p->rChild);

    // Count Leaf Nodes
    if (countLeafNodes)
    {
      if (p->lChild == NULL && p->mChild == NULL && p->rChild == NULL)
        return x + y + z + 1;
    }
    // Count Non-Leaf Nodes
    else if (p->lChild != NULL || p->mChild != NULL || p->rChild != NULL)
      return x + y + z + 1;

    return x + y + z;
  }
}

// Method to Get Tree Height
template <class NodeType>
int TernNode<NodeType>::getHeight(TernNodePtr<NodeType> p)
{
  int x = 0, y = 0, z = 0;

  // Check p Node
  if (p == NULL)
    return 0;

  x = this->getHeight(p->lChild);
  y = this->getHeight(p->mChild);
  z = this->getHeight(p->rChild);

  // Get the Greastest Height
  if (x >= y && x >= z)
    return x + 1;
  else if (y >= x && y >= z)
    return y + 1;
  else
    return z + 1;
}

#endif