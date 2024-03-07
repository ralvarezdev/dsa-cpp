#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <typeinfo>

#include "base.h"
#include "../queue/base.h"
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
class NumberBinaryTree : public BinaryTree<NodeType>
{
private:
  int whitelist = {'l', 'r'};
  int length = 2;

  // Private Methods
  NodeType isNodeType(string);
  NodeType getNodeType(string, bool);

  // Private Methods for Input Validation
  int getInteger(string message, int low, int high);
  int getChar(string askMessage, int whitelist[], int length, string errMessage);

public:
  // Public Constructors
  NumberBinaryTree(NodeType);

  // Public Methods
  void insert(NodeType data);
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
  QueueLinkedList<BinNodePtr<NodeType>> *q = new QueueLinkedList<BinNodePtr<NodeType>>(NULL);

  // Set Error
  this->error = error;

  // Message
  cout << "CREATING BINARY TREE\n"
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

    // Check if there was an Error
    if (p == NULL)
      continue;

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

  // Deallocate Memory
  delete q;
}

// Method to Ask for Integer Input
template <class NodeType>
int NumberBinaryTree<NodeType>::getInteger(string message, int low, int high)
{
  string temp;
  int amount;

  while (true)
    try // Get Integer
    {
      cout << message << ": ";
      getline(cin, temp);
      amount = stoi(temp);

      if (amount >= low && amount <= high)
        return amount;
      else
        // Number Out of Range
        throw(-1);
    }
    catch (...)
    {
      ostringstream stream;

      stream << "The Number is Out of Range"
             << " [" << low << '-' << high << "]";

      this->pressEnterToCont(stream.str(), true);
    }
}

// Method to Ask for Character Given a Whitelist
template <class NodeType>
int NumberBinaryTree<NodeType>::getChar(string askMessage, int whitelist[], int length, string errMessage)
{
  string input;

  // Ask for String Input
  while (true)
    try
    {
      cout << askMessage << ": ";
      getline(cin, input);

      // Get First Character as Lowercase
      c = tolower(input[0]);

      // Input Should be Found in Characters Whitelist
      for (int i = 0; i < length; i++)
        if (whitelist[i] == c)
          return c;

      throw(-1);
    }
    catch (...)
    {
      this->pressEnterToCont(errMessage); // Ignore First Character if it's not in Whitelist
      cout << '\n';
    }
}

// Method to Insert Node to Binary Tree, as the User Wants
template <class NodeType>
void NumberBinaryTree<NodeType>::insert(NodeType data)
{
  BinNodePtr<NodeType> q = NULL, p, newNode;
  NodeInfoPtr<NodeType> info, t;

  ostringstream message, errMessage;
  int iter = 0, childPos, l, r;

  // Get Valid Characters to Move throughout Binary Tree
  l = this->whitelist[0];
  r = this->whitelist[1];

  // Initialize Doubly Linked List
  DoublyLinkedList<NodeInfoPtr<NodeType>> *list = new DoublyLinkedList<NodeInfoPtr<NodeType>>(NULL);

  // Header Message
  cout << "INSERTING NODE TO BINARY TREE\n\n";

  // Set Error Message
  errMessage << "NOTES:\n"
             << "- Enter '" << l << "' or '" << toupper(l) << "' for Node's Left Child\n"
             << "- Enter '" << r << "' or '" << toupper(r) << "' for Node's Right Child\n\n";

  // Create Node
  newNode = new BinNodePtr<NodeType>(data);

  // Chekc if Root is NULL
  if (this->root != NULL)
  {
    cout << "Inserting Node as Root\n";
    this->root = newNode;

    delete list;
    return;
  }

  // Set Root as p
  p = this->root;

  // Push Back Node Data to List
  info = new NodeInfoPtr<NodeType>{p->data, 'R'};
  list->push(info);

  while (true)
  {
    // Set Message
    message.str("");
    message.clear();

    // Insert it as a New Child
    if (p == NULL)
    {
      cout << "Inserting Leaf Node as a New Child [" << childPos << "]\n";

      if (childPos == l)
        q->lChild = newNode;
      else
        q->rChild = newNode;

      break;
    }

    // Print Node Data
    cout << "Level: " << level << '\n';

    // Print Parents
    for (int i = 0; i < iter; i++)
    {
      // Get Parent Node Info
      t = list->get(i);
      cout << "Parent " << i + 1 << '[' << t->desc << "]: " << t->data;
    }

    // Asks to the User to Insert Node at p
    if (this->booleanQuestion("Do you want to Insert the Node there?"))
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
      cout << "INSERTING OLD NODE\n"
           << errMessage.str();

      childPos = this->getChar("Where do you want to Insert Old Node", this->whitelist, errMessage.str());

      if (childPos == l)
        newNode->lChild = p;
      else
        newNode->rChild = p;

      break;
    }

    // Get to Which Child to Move
    cout << "MOVING THROUGH TREE\n"
         << errMessage.str();

    childPos = this->getChar("Which Child do you want to Move to", this->whitelist, errMessage.str());

    // Move to Child
    q = p;

    if (childPos == l)
      p = p->lChild;
    else
      p = p->rChild;

    // Increase Tree Level and Path Counter
    iter++;
  }

  // Deallocate Memory
  delete l;
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