#include <string>
#include <iostream>
#include <sstream>
#include <filesystem>

#include "../../../data-structures/binary-search-tree/number.h"
#include "../../../data-structures/binary-tree/number.h"
#include "../../../data-structures/queue/base.h"

#include "lib/terminal/ansiEsc.h"
#include "lib/terminal/input.h"
#include "lib/namespaces.h"

using namespace std;

using namespace terminal;

// --- Function Prototypes
void helpMessage();
void emptyQueue(QueueLinkedList<int> *);
void getPreorderNodesData(QueueLinkedList<int> *);

int main(int argc, char **argv)
{
  // Desynchronize C++ Streams from C I/O Operations to Increase Performance
  std::ios::sync_with_stdio(false);

  // Declare Binary Tree and Binary Search Tree
  NumberBinaryTree<int> *binTree = NULL;
  NumberBinarySearchTree<int> *binSearchTree = NULL;
  QueueLinkedList<int> q(binaryTree::error);

  // - Program Status Variables
  bool exit, confirmation;
  string inputWord;
  int data, intCmd, timesExec = 0;
  char cmd;

  string binSearchNotInit = "\nBinary Search Tree hasn't been Initialized";

  while (!exit) // Main While Loop of the Program
  {
    // Check if Invoke Command Contains Program's Commands
    if (timesExec == 0 && argc > 1)
      cmd = argv[1][0];
    else
    {
      // Clear Screen
      cout << terminal::clear;

      // Print Help Message
      helpMessage();

      // Print New Line
      cout << '\n';

      // Get Command
      cmd = getChar("Enter Command: ");
    }

    // Increase Counter
    timesExec++;

    switch (cmd)
    {
    case binaryTree::cmds::binSearchInit:
      // Clear Binary Search Tree
      if (binSearchTree != NULL)
        delete binSearchTree;

      // Clear Screen
      cout << terminal::clear;

      // Asks if the User wants to Add Some Nodes
      confirmation = booleanQuestion("Do you want to Insert Some Nodes?");

      // Initialize Binary Search Tree with No Nodes
      if (!confirmation)
      {
        binSearchTree = new NumberBinarySearchTree<int>(binaryTree::error);
        break;
      }

      // Ask for Nodes' Data
      getPreorderNodesData(&q);

      // Initialize Binary Search Tree
      binSearchTree = new NumberBinarySearchTree<int>(&q, binaryTree::error);

      break;

    case binaryTree::cmds::binSearchInsert:
      // Check if Binary Search Tree has been Initialized
      if (binSearchTree == NULL)
      {
        pressEnterToCont(binSearchNotInit, true);
        break;
      }

      // Clear Screen
      cout << terminal::clear;

      // Ask for Nodes' Data
      getPreorderNodesData(&q);

      // Insert Nodes
      binSearchTree->insert(&q);

      break;

    case binaryTree::cmds::binSearchRemove:
      // Check if Binary Search Tree has been Initialized
      if (binSearchTree == NULL)
      {
        pressEnterToCont(binSearchNotInit, true);
        break;
      }

      // Clear Screen
      cout << terminal::clear;

      // Ask for Nodes' Data
      getPreorderNodesData(&q);

      // Remove Nodes
      binSearchTree->remove(&q);

      break;

    case binaryTree::cmds::binSearchFind:
      // Check if Binary Search Tree has been Initialized
      if (binSearchTree == NULL)
      {
        pressEnterToCont(binSearchNotInit, true);
        break;
      }

      // Clear Screen
      cout << terminal::clear;

      // Ask for Node's Data
      data = getInteger("Enter Node's Data", binaryTree::minData, binaryTree::maxData, binaryTree::error);

      // Check if Binary Search Tree Contains Node's Data
      if (binSearchTree->search(data))
      {
        pressEnterToCont("Data Found in Binary Search Tree");
        break;
      }

      pressEnterToCont("Data not Found in Binary Search Tree");
      break;

    case binaryTree::cmds::binSearchPrint:
      // Check if Binary Search Tree has been Initialized
      if (binSearchTree == NULL)
      {
        pressEnterToCont(binSearchNotInit, true);
        break;
      }

      // Clear Screen
      cout << terminal::clear;

      // Print Preorder, Inorder and Postorder Traversals
      printTitle("Binary Search Tree Preorder");
      binSearchTree->preorder();

      printTitle("Binary Search Tree Inorder");
      binSearchTree->inorder();

      printTitle("Binary Search Tree Postorder");
      binSearchTree->postorder();

      pressEnterToCont("Press ENTER to Continue");

    case binaryTree::cmds::help:
      break;

    case binaryTree::cmds::exit:
      // Confirmation Message
      exit = booleanQuestion("\nAre you SURE to Exit");
      break;

    default:
      // Command not Found
      pressEnterToCont("\nERROR: Command not Found", true);
      break;
    }
  }

  // Deallocate Memory
  delete binTree, binSearchTree;
}

// --- Functions

// Function to Print Help Message in the Terminal
void helpMessage()
{
  cout << clear;
  printTitle("WELCOME TO BINARY XTREE");
  cout << "Binary Tree Manipulation Commands\n"
       << tab1 << addBrackets<int>(binaryTree::cmds::binInit) << " Initialize Tree\n"
       << tab1 << addBrackets<int>(binaryTree::cmds::binInsert) << " Insert Node\n"
       << tab1 << addBrackets<int>(binaryTree::cmds::binRemove) << " Remove Node\n"
       << tab1 << addBrackets<int>(binaryTree::cmds::binPrint) << " Print Inorder, Preorder, Postorder\n"
       << "Binary Search Tree Manipulation Commands\n"
       << tab1 << addBrackets<int>(binaryTree::cmds::binSearchInit) << " Initialize Tree\n"
       << tab1 << addBrackets<int>(binaryTree::cmds::binSearchInsert) << " Insert Node\n"
       << tab1 << addBrackets<int>(binaryTree::cmds::binSearchRemove) << " Remove Node\n"
       << tab1 << addBrackets<int>(binaryTree::cmds::binSearchFind) << " Search Node\n"
       << tab1 << addBrackets<int>(binaryTree::cmds::binSearchPrint) << " Print Inorder, Preorder, Postorder\n"
       << "Other Commands:\n"
       << tab1 << addBrackets<int>(binaryTree::cmds::help) << " Help\n"
       << tab1 << addBrackets<int>(binaryTree::cmds::exit) << " Exit\n";
}

// Function to Empty Queue
void emptyQueue(QueueLinkedList<int> *q)
{
  // Empty Queue
  while (!q->isEmpty())
    q->dequeue();
}

// Function to Ask for Nodes' Data
void getPreorderNodesData(QueueLinkedList<int> *q)
{
  // Clear Queue
  if (q != NULL)
    emptyQueue(q);

  ostringstream msg;
  int data;

  msg << "Enter Nodes' Data to Insert in Preorder. Enter '"
      << binaryTree::error
      << "' to Stop Asking for Input";

  // Print Help Message
  printTitle(msg.str());

  while (true)
  {
    // Ask for Node's Data
    data = getInteger("Enter Node's Data", binaryTree::minData, binaryTree::maxData, binaryTree::error);

    // Stop Asking for Input
    if (data == binaryTree::error)
      break;

    // Push Data to Queue
    q->enqueue(data);
  }
}