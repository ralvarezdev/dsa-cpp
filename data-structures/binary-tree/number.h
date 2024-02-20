#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <typeinfo>

#include "base.h"
#include "../queue/base.h"
#include "../nodes/binNode.h"

using std::cin;
using std::cout;
using std::ostringstream;
using std::string;

#ifndef NUMBER_BIN_TREE
#define NUMBER_BIN_TREE

// NUMBER BINARY TREE CLASS

template <class NodeType>
class NumberBinaryTree : public BinaryTree<NodeType>
{
private:
  // Private Methods
  NodeType isNodeType(string);
  NodeType getNodeType(string, bool);

public:
  // Public Constructors
  NumberBinaryTree(NodeType);
};

// Binary Tree Constructors

// Creates a Binary Tree with the Help of Queues
// NOTE: This will only work with Int, Float and Double Data Types with Structures or Classes as NodeType. If you're working with any of them, you must
// create a Child Class from Binary Tree and overwrite the Constructor
template <class NodeType>
NumberBinaryTree<NodeType>::NumberBinaryTree(NodeType error)
{
  BinNodePtr<NodeType> p, t;
  NodeType data;
  string input;
  ostringstream message;

  // Initialize Queue
  QueueLinkedList<BinNodePtr<NodeType>> *q = new QueueLinkedList<BinNodePtr<NodeType>>(error);

  // Set Error
  this->error = error;

  // Message
  cout << "C-R-E-A-T-I-N-G  B-I-N-A-R-Y  T-R-E-E\n"
       << "NOTE: Enter '" << error << "' to Set Node as NULL\n\n";

  // Get Root Data
  data = getNodeType("Enter Root Node Data", false);

  // Create Root Node
  this->root = new BinNodePtr<NodeType>(data);

  // Push Root Node to Queue
  q->enqueue(this->root);

  while (!q->isEmpty())
  {
    p = q->dequeue();

    // Set Message
    message.str("");
    message.clear();
    message << "Enter Left Child Node Data of " << p->data;

    // Get Left Child Data
    data = getNodeType(message.str(), true);

    if (data != this->error)
    {
      // Create t Node
      t = new BinNodePtr<NodeType>(data);

      // Set t as Left Child of p
      p->lChild = t;

      // Push t to Queue
      q->enqueue(t);
    }

    // Set Message
    message.str("");
    message.clear();
    message << "Enter Right Child Node Data of " << p->data;

    // Get Right Child Data
    data = getNodeType(message.str(), true);

    if (data != this->error)
    {
      // Create t Node
      t = new BinNodePtr<NodeType>(data);

      // Set t as Right Child of p
      p->rChild = t;

      // Push t to Queue
      q->enqueue(t);
    }
  }
}

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
    cin >> input;

    // Check input Data
    data = this->isNodeType(input);

    // Errors are Allowed, so Return Data, even if it's an Error
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
      throw(-1);

    return conversion;
  }
  catch (...)
  {
    return this->error; // input Couldn't be Converted to NodeType
  }
}

#endif