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
void clearQueue(QueueLinkedList<int> *, QueueLinkedList<int> *);
void askNodesData(QueueLinkedList<int> *);

int main(int argc, char **argv)
{
  // Desynchronize C++ Streams from C I/O Operations to Increase Performance
  std::ios::sync_with_stdio(false);

  // Declare Binary Tree and Binary Search Tree
  NumberBinaryTree<int> *binTree = NULL;
  NumberBinarySearchTree<int> *binSearchTree = NULL;
  QueueLinkedList<int> *q, *t = NULL;

  // - Program Status Variables
  bool exit, confirmation;
  string inputWord;
  int data, intCmd, timesExec = 0;
  binaryTree::cmds cmd;

  string binSearchNotInit = "Binary Search Tree hasn't been Initialized";

  while (!exit) // Main While Loop of the Program
  {
    // Check if Invoke Command Contains Program's Commands
    if (timesExec == 0 && argc > 1)
    { // Checks if it's a Command
      inputWord = argv[1];
      try
      {
        // Try to Get Command
        cmd = binaryTree::cmds(stoi(inputWord));
      }
      catch (...)
      {
        // Throw Error Message
        pressEnterToCont("ERROR: Command not Found", true);
        break;
      }
    }
    else
    {
      // Print Help Message
      helpMessage();

      // Print New Line
      cout << '\n';

      // Get Command
      intCmd = getInteger("Enter Command", 1, binaryTree::cmdNull);
      cmd = binaryTree::cmds(intCmd);
    }

    // Increase Counter
    timesExec++;

    switch (cmd)
    {
    case binaryTree::binSearchInit:
      // Clear Binary Search Tree
      if (binSearchTree != NULL)
        delete binSearchTree;

      // Asks if the User wants to Add Some Nodes
      confirmation = booleanQuestion("Do you want to Insert Some Nodes?");

      // Initialize Binary Search Tree with No Nodes
      if (!confirmation)
      {
        binSearchTree = new NumberBinarySearchTree<int>(binaryTree::error);
        break;
      }

      // Ask for Nodes' Data
      askNodesData(q);

      // Initialize Binary Search Tree
      binSearchTree = new NumberBinarySearchTree<int>(q, binaryTree::error);

      // Clear Queue
      clearQueue(q, t);

      break;

    case binaryTree::binSearchInsert:
      // Check if Binary Search Tree has been Initialized
      if (binSearchTree == NULL)
      {
        pressEnterToCont(binSearchNotInit, true);
        break;
      }

      // Ask for Nodes' Data
      askNodesData(q);

      // Insert Nodes
      binSearchTree->insert(q);

      // Clear Queue
      clearQueue(q, t);

      break;

    case binaryTree::binSearchRemove:
      // Check if Binary Search Tree has been Initialized
      if (binSearchTree == NULL)
      {
        pressEnterToCont(binSearchNotInit, true);
        break;
      }

      // Ask for Nodes' Data
      askNodesData(q);

      // Remove Nodes
      binSearchTree->remove(q);

      // Clear Queue
      clearQueue(q, t);

      break;

    case binaryTree::binSearchFind:
      // Check if Binary Search Tree has been Initialized
      if (binSearchTree == NULL)
      {
        pressEnterToCont(binSearchNotInit, true);
        break;
      }

      // Ask for Node's Data
      data = getInteger("Enter Node's Data", binaryTree::minData, binaryTree::maxData);

      // Check if Binary Search Tree Contains Node's Data
      if (binSearchTree->search(data))
      {
        pressEnterToCont("Data Found in Binary Search Tree");
        break;
      }

      pressEnterToCont("Data not Found in Binary Search Tree");
      break;

    case binaryTree::binSearchPrint:
      // Check if Binary Search Tree has been Initialized
      if (binSearchTree == NULL)
      {
        pressEnterToCont(binSearchNotInit, true);
        break;
      }

      // Print Preorder, Inorder and Postorder Traversals
      printTitle("Binary Search Tree Preorder");
      binSearchTree->preorder();

      printTitle("Binary Search Tree Inorder");
      binSearchTree->inorder();

      printTitle("Binary Search Tree Postorder");
      binSearchTree->postorder();

      pressEnterToCont("Press ENTER to Continue");

    case binaryTree::help:
      break;

    case binaryTree::exit:
      // Confirmation Message
      exit = booleanQuestion("Are you SURE to Exit");
      break;

    default:
      // Command not Found
      pressEnterToCont("ERROR: Command not Found", true);
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
       << tab1 << addBrackets<int>(binaryTree::binInit) << " Initialize Tree\n"
       << tab1 << addBrackets<int>(binaryTree::binInsert) << " Insert Node\n"
       << tab1 << addBrackets<int>(binaryTree::binRemove) << " Remove Node\n"
       << tab1 << addBrackets<int>(binaryTree::binPrint) << " Print Inorder, Preorder, Postorder\n"
       << "Binary Search Tree Manipulation Commands\n"
       << tab1 << addBrackets<int>(binaryTree::binSearchInit) << " Initialize Tree\n"
       << tab1 << addBrackets<int>(binaryTree::binSearchInsert) << " Insert Node\n"
       << tab1 << addBrackets<int>(binaryTree::binSearchRemove) << " Remove Node\n"
       << tab1 << addBrackets<int>(binaryTree::binSearchFind) << " Search Node\n"
       << tab1 << addBrackets<int>(binaryTree::binSearchPrint) << " Print Inorder, Preorder, Postorder\n"
       << "Other Commands:\n"
       << tab1 << addBrackets<int>(binaryTree::help) << " Help\n"
       << tab1 << addBrackets<int>(binaryTree::exit) << " Exit\n";
}

// Function to Clear Queue
void clearQueue(QueueLinkedList<int> *q, QueueLinkedList<int> *t)
{
  // Check q
  if (q != NULL)
  {
    t = q;
    q = NULL;
    delete t;
  }
}

// Function to Ask for Nodes' Data
void askNodesData(QueueLinkedList<int> *q)
{
  ostringstream msg;
  int data;

  msg << "Enter Nodes' Data to Insert. Enter '"
      << binaryTree::error
      << "' to Stop Asking for Input";

  // Print Help Message
  pressEnterToCont(msg.str());

  while (true)
  {
    // Ask for Node's Data
    data = getInteger("Enter Node's Data", binaryTree::minData, binaryTree::maxData);

    // Stop Asking for Input
    if (data == binaryTree::error)
      break;

    // Push Data to Queue
    q->enqueue(data);
  }
}