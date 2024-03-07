#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>

#include "../nodes/binNode.h"

using std::cin;
using std::cout;
using std::getline;
using std::ostringstream;
using std::string;

#ifndef BIN_TREE
#define BIN_TREE

// BINARY TREE CLASS

template <class NodeType>
class BinaryTree
{
protected:
  BinNodePtr<NodeType> root = NULL;

  NodeType error;

  // Protected Methods for Input Validation
  void pressEnterToCont(string message);
  bool booleanQuestion(string message);

public:
  // Constructors
  BinaryTree(NodeType);
  BinaryTree(NodeType, NodeType);

  // Public Methods
  void preorder() { this->root->preorder(); };
  void inorder() { this->root->inorder(); };
  void postorder() { this->root->postorder(); };
  void levelOrder() { this->root->levelOrder(); };
  int countNodes() { this->root->countNodes(); };
  int countTypeNodes(bool countLeafNodes) { this->root->countTypeNodes(countLeafNodes); };
  int getHeight() { this->root->getHeight(); };
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

// Method to Ask a Boolean Question
template <class NodeType>
bool BinaryTree<NodeType>::booleanQuestion(string message)
{
  string input;
  char c;

  while (true)
  {
    cout << "- " << message << " [y/N] ";
    getline(cin, input);

    c = tolower(input[0]);
    cout << c;

    if (c == 'y')
    {
      cout << '\n';
      return true;
    }
    else if (c == 'n')
    {
      cout << '\n';
      return false;
    }

    // Print Error Message
    this->pressEnterToCont("ERROR: It's a Yes/No Question. You must type 'y', 'Y' or 'n', 'N'", true);
  }
}

// Method to Stop the Program Flow while the User doesn't press the ENTER key
template <class NodeType>
void BinaryTree<NodeType>::pressEnterToCont(string message)
{
  string _;

  cout << message << '\n';
  getline(cin, _);
}

#endif
