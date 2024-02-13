#include <string>
#include <random>
#include <iostream>

#include "lib/namespaces.h"
#include "lib/terminal/ansiEsc.h"
#include "lib/terminal/input.h"
#include "../../../data-structures/stack/number.h"
#include "../../../data-structures/doubly-linked-lists/number.h"

/*
NOTE: For this practice, it's required to sort 3 stacks (I tried to expand this number by N stacks),
with 3 nodes each (I also tried to expand by N nodes). We're only allowed to get last node data at given stack.
My algorithm to solve this problem is based on the Hanoi Tower Problem. Because we will only know last node at each stack,
I'll need at least two linked lists to sort the stack. However, I create the same number of linked lists as stacks,
to print faster each node at each stack.
*/

/*
Stack Representation

| 2   |
| 999 |
| 3   |
| 25  |
| 1   |
| 66  |
*/

using std::cin;
using std::cout;
using std::random_device;
using std::uniform_int_distribution;

using namespace stacks;

// --- Function Prototypes
void helpMessage();

int main(int argc, char **argv)
{
  // Desynchronize C++ Streams from C I/O Operations to Increase Performance
  std::ios::sync_with_stdio(false);

  // Print Title
  printTitle("SORTING STACKS PROBLEM");
  cout << '\n';

  // Ask for Number of Nodes for each Stack
  const int stackLen = getInteger("Enter the Number of Nodes for each Stack", stacks::minNodes, stacks::maxNodes);

  // Check nStacks
  if (stacks::nStacks < 3)
  {
    printTitle("ERROR: This Algorithm Requires at Least 3 Stacks to Sort them", true);
    return -1;
  }

  // Create Stacks Linked List
  NumberStackLinkedList<int> **stacksArray = new NumberStackLinkedList<int> *[stacks::nStacks];
  NumberDoublyLinkedList<int> **listsArray = new NumberDoublyLinkedList<int> *[stacks::nStacks];

  // Random Number Generator
  random_device rd;

  // Random Integer Distribution
  uniform_int_distribution<int> dist(stacks::minNodeValue, stacks::maxNodeValue);

  int random;

  for (int n = 0; n < stacks::nStacks; n++)
  {
    // Create Stack and Doubly Linked List
    NumberStackLinkedList<int> *stack = new NumberStackLinkedList<int>();
    NumberDoublyLinkedList<int> *list = new NumberDoublyLinkedList<int>();

    // Create Random Nodes Values for Each
    for (int i = 0; i < stackLen; i++)
    {
      // Generate Random Node Values
      random = dist(rd);

      /*
      // Testing Data Structures
      cout << random << ' ' << (*stack).getLength() << ' ' << (*list).getLength() << '\n';
      */

      // Push Random Node Value to Stack and Doubly Linked List
      (*stack).push(random);
      (*list).push(random);
    }

    // Testing Data Structures
    cout << "\nStack " << n + 1 << " Top: " << (*stack).top();
    /*
     */

    // Added Stack and Doubly Linked List to their Corresponding Array
    stacksArray[n] = stack;
    listsArray[n] = list;
  }

  // Check Random Numbers
  for (int n = 0; n < stacks::nStacks; n++)
  {
    cout << "\n\nStack " << n + 1 << '\n';
    (*listsArray[n]).print();
  }

  // Deallocate Memory
  delete[] stacksArray;
  delete[] listsArray;
}