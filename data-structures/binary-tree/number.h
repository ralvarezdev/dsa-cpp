#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <typeinfo>

#include "namespaces.h"
#include "../queue/base.h"
#include "../nodes/binNode.h"
#include "../doubly-linked-lists/base.h"

using std::cin;
using std::cout;
using std::ostringstream;
using std::string;

#ifndef NUMBER_BIN_TREE
#define NUMBER_BIN_TREE

// AUXILIARY STRUCTURE
template <typename NodeType>
struct NodeInfo
{
  NodeType data; // Holds Node's Data
  int desc;      // Uses a Character to Describe Node's Position in Tree
};

// NodeInfoPtr Definition
template <typename NodeType>
using NodeInfoPtr = NodeInfo<NodeType> *;

// NUMBER BINARY TREE CLASS

template <class NodeType>
class NumberBinaryTree
{
private:
  const int NULL_CHILD = -1;
  const int LOCK_TREE = -2;

  BinNodePtr<NodeType> root = NULL;
  NodeType error;

  int whitelist[2] = {'l', 'r'};
  int length = 2;

  // Private Methods
  NodeType isNodeType(string);
  NodeType getNodeType(string, bool);

public:
  // Public Constructors
  NumberBinaryTree(NodeType);
  NumberBinaryTree() : NumberBinaryTree<NodeType>(-1){};

  // Public Methods
  void preorder() { this->root->preorder(); };
  void inorder() { this->root->inorder(); };
  void postorder() { this->root->postorder(); };
  void levelOrder() { this->root->levelOrder(); };
  int countNodes() { return this->root->countNodes(); };
  int countTypeNodes(bool countLeafNodes) { return this->root->countTypeNodes(countLeafNodes); };
  int getHeight() { return this->root->getHeight(); };
  NodeType getError() { return this->error; };

  void insert(NodeType data);
};

// Binary Tree Constructors

// Creates a Binary Tree with the Help of Queues
// NOTE: This will only work with Int, Float and Double Data Types with Structures or Classes as NodeType. If you're not Working with any of them, you must
// Create a Child Class from Binary Tree and overwrite the Constructor
template <class NodeType>
NumberBinaryTree<NodeType>::NumberBinaryTree(NodeType error)
{
  BinNodePtr<NodeType> p, t;
  NodeType data;
  bool lockTree = false;
  string input;
  ostringstream message;

  // Initialize Queue
  QueueLinkedList<BinNodePtr<NodeType>> *q = new QueueLinkedList<BinNodePtr<NodeType>>(NULL);

  // Set Error
  this->error = error;

  // Message
  cout << "CREATING BINARY TREE\n"
       << "NOTES:\n"
       << "1. Enter '" << this->NULL_CHILD << "' to Set Node as NULL\n"
       << "2. Enter '" << this->LOCK_TREE << "' to Stop Asking for New Nodes\n\n";

  // Get Root Data
  data = getNodeType("Enter Root Node Data", false);

  // Create Root Node
  this->root = new BinNode<NodeType>(data);

  // Push Root Node to Queue
  q->enqueue(this->root);

  while (!q->isEmpty() && !lockTree)
  {
    p = q->dequeue();

    for (int i = 0; i < 2; i++)
    {
      // Set Message
      message.str("");
      message.clear();
      message << "Enter " << ((i == 0) ? "Left" : "Right") << " Child Node Data of " << p->data;

      // Get Child Data
      data = getNodeType(message.str(), true);

      // Check if the Tree is Completed
      lockTree = data == this->LOCK_TREE;

      if (lockTree)
        break;

      if (data != this->error)
      {
        // Create t Node
        t = new BinNode<NodeType>(data);

        // Check which Child is being Set
        if (i == 0)
          // Set t as Left Child of p
          p->lChild = t;

        else
          // Set t as Right Child of p
          p->rChild = t;

        // Push t to Queue
        q->enqueue(t);
      }
    }
  }

  // Deallocate Memory
  delete q;
}

// Method to Insert Node to Binary Tree, as the User Wants
template <class NodeType>
void NumberBinaryTree<NodeType>::insert(NodeType data)
{
  BinNodePtr<NodeType> q, p, newNode;
  NodeInfoPtr<NodeType> info, t;
  ostringstream message, errMessage;
  int iter = 0, childPos, l, r;

  // Get Valid Characters to Move throughout Binary Tree
  l = this->whitelist[0];
  r = this->whitelist[1];

  // Initialize Doubly Linked List
  DoublyLinkedList<NodeInfoPtr<NodeType>> *list = new DoublyLinkedList<NodeInfoPtr<NodeType>>(NULL);

  // Set Error Message
  errMessage << "\nNOTES:\n"
             << "- Enter '" << char(l) << "' or '" << char(toupper(l)) << "' for Node's Left Child\n"
             << "- Enter '" << char(r) << "' or '" << char(toupper(r)) << "' for Node's Right Child\n";

  // Create Node
  newNode = new BinNode<NodeType>(data);

  // Check if Root is NULL
  if (this->root == NULL)
  {
    cout << "Inserting Node as Root\n";
    this->root = newNode;

    // Deallocate Memory
    delete list;

    return;
  }

  // Set Root as p
  p = this->root;

  while (p != NULL)
  {
    // Push Back Node Data to List
    info = new NodeInfo<NodeType>{p->data, iter};
    list->pushBack(info);

    // Get Parent Node Info
    t = list->get(iter);
    message << "Parent [" << t->desc << "]: " << t->data << '\n';

    // Print Node Data
    cout << binaryTree::clear
         << "Level: " << iter << '\n'
         << message.str();

    // Asks to the User to Insert Node at p
    if (binaryTree::booleanQuestion("Do you want to Insert the Node here?"))
    {
      // Get Node's Data
      data = p->data;

      // Check if it's Root Node
      if (p == this->root)
        this->root = newNode;

      // Assign as Child from q Node
      else if (childPos == l)
        q->lChild = newNode;

      else
        q->rChild = newNode;

      // Asks wether to Insert p Node as Either Left or Right Child of New Node
      cout << "INSERTING OLD NODE\n";

      childPos = binaryTree::getChar("Where do you want to Insert Old Node", this->whitelist, this->length, errMessage.str());

      if (childPos == l)
        newNode->lChild = p;

      else
        newNode->rChild = p;

      return;
    }

    // Get to Which Child to Move
    cout << "MOVING THROUGH TREE\n";

    childPos = binaryTree::getChar("Which Child do you want to Move to", this->whitelist, this->length, errMessage.str());

    // Move to Child
    q = p;

    if (childPos == l)
      p = p->lChild;

    else
      p = p->rChild;

    // Increase Tree Level and Path Counter
    iter++;
  }

  // Insert it as a New Child
  if (p == NULL)
  {
    cout << "Inserting Leaf Node as a New Child [" << char(childPos) << "]\n";

    if (childPos == l)
      q->lChild = newNode;

    else
      q->rChild = newNode;
  }

  // Deallocate Memory
  delete list;
}

// Method to Delete Node from Binary Tree, as the User Wants

// Method to Get Data of NodeType Data Type
template <class NodeType>
NodeType NumberBinaryTree<NodeType>::getNodeType(string message, bool errorAllowed)
{
  string input;
  NodeType data;

  while (true)
  {
    // Get Node Data
    cout << message << ": ";
    getline(cin, input);

    // Check input Data
    data = this->isNodeType(input);

    // Errors are Allowed. So, Return Data, even if it's an Error
    if (errorAllowed)
      return data;

    // Check Data
    if (data != this->error)
      return data;
  }
}

// Method to Check if Data Input can be Converted to NodeType Data Type
template <class NodeType>
NodeType NumberBinaryTree<NodeType>::isNodeType(string input)
{
  NodeType conversion;

  try
  {
    // Checks if it's an Int
    if (typeid(NodeType) == typeid(int) || typeid(NodeType) == typeid(const int))
      conversion = stoi(input); // Try to Get Integer

    // Checks if it's a Float
    else if (typeid(NodeType) == typeid(float) || typeid(NodeType) == typeid(const float))
      conversion = stof(input); // Try to Get Float

    // Checks if it's a Double
    else if (typeid(NodeType) == typeid(double) || typeid(NodeType) == typeid(const double))
      conversion = stod(input); // Try to Get Double

    // NodeType isn't Supported
    else
      throw(this->error);

    return conversion;
  }
  catch (...)
  {
    return this->error; // input Couldn't be Converted to NodeType
  }
}

#endif