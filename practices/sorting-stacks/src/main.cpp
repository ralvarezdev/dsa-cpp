#include <string>
#include <random>
#include <algorithm>
#include <sstream>
#include <iostream>

#include "lib/namespaces.h"
#include "lib/algorithm/modHanoi.h"
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
using std::fill;
using std::left;
using std::ostringstream;
using std::random_device;
using std::uniform_int_distribution;

using namespace stacks;

// --- Function Prototypes
void printStacks(NumberDoublyPtr *, int);

int main(int argc, char **argv)
{
  // Length of Biggest Stack
  int maxLength;

  // Auxiliary Stacks Used to Sort Current Stack
  int auxIndex, mainAuxIndex;

  // Random Number Generator
  random_device rd;

  // Desynchronize C++ Streams from C I/O Operations to Increase Performance
  std::ios::sync_with_stdio(false);

  // Print Title
  printTitle("SORTING STACKS PROBLEM");
  cout << '\n';

  // Ask for Number of Nodes for each Stack
  const int stackLen = getInteger("Enter the Number of Nodes for each Stack", stacks::minNodes, stacks::maxNodes);

  // Variable that Stores the Length of the Biggest Stack
  maxLength = stackLen;

  // Check nStacks
  if (stacks::nStacks < stacks::minStacks)
  {
    printTitle("ERROR: This Algorithm Requires at Least 3 Stacks to Sort them", true);
    return -1;
  }
  if (stacks::nStacks > stacks::maxStacks)
  {
    printTitle("WARNING: nStacks is too Big. Stacks could Look Wrong because of Terminal Width", true);
    printTitle("- If you're Sure about your Choice, Modify maxStacks in stacks Namespace, and Run this Program Again", true);
    return -1;
  }

  // Create Stacks and Doubly Linked List
  NumberStackPtr *stacksArray = new NumberStackPtr[stacks::nStacks];
  NumberDoublyPtr *listsArray = new NumberDoublyPtr[stacks::nStacks];

  // Random Integer Distribution
  uniform_int_distribution<int> dist(stacks::minNodeValue, stacks::maxNodeValue);

  int random;
  NumberStackPtr stack;
  NumberDoublyPtr list;

  for (int n = 0; n < stacks::nStacks; n++)
  {
    // Create Stack and Doubly Linked List
    stack = new NumberStackLinkedList<int>();
    list = new NumberDoublyLinkedList<int>();

    // Create Random Nodes Values for Each
    for (int i = 0; i < stackLen; i++)
    {
      // Generate Random Node Values
      random = dist(rd);

      // Testing Data Structures
      /*
      cout << random << ' ' << (*stack).getLength() << ' ' << (*list).getLength() << '\n';
      */

      // Push Random Node Value to Stack and Doubly Linked List
      stack->push(random);
      list->push(random);
    }

    /*
    // Testing Data Structures
    cout << "\nStack " << n + 1 << " Top: " << (*stack).top();
    */

    // Added Stack and Doubly Linked List to their Corresponding Array
    stacksArray[n] = stack;
    listsArray[n] = list;
  }

  /*
  // Testing Stack Random Numbers
  for (int n = 0; n < stacks::nStacks; n++)
  {
    cout << "\n\nStack " << n + 1 << '\n';
    listsArray[n]->print();
  }
   */

  // Initial State
  printStacks(listsArray, maxLength);

  for (int currStack = 0; currStack < stacks::nStacks; currStack++)
  {
    // Sort Last Stack
    if (currStack + 1 == stacks::nStacks)
    {
      // Third to Last Stack
      mainAuxIndex = currStack - 2;
      // Second to Last Stack
      auxIndex = currStack - 1;
    }
    // Sort Second to Last Stack
    else if (currStack + 2 == stacks::nStacks)
    {
      // Third to Last Stack
      mainAuxIndex = currStack - 2;
      // Last Stack
      auxIndex = currStack + 1;
    }
    else
    {
      // Second Stack Next to the One to be Sorted
      mainAuxIndex = currStack + 2;
      // Stack Next to the One to be Sorted
      auxIndex = currStack + 1;
    }

    // First Iteration
    moveAtoB(currStack, mainAuxIndex, stacksArray, listsArray);

    // Increase Length
    maxLength++;

    // Print Update
    printStacks(listsArray, maxLength);

    int currStackTop;

    // Sort Stack Until All Nodes are Pushed to Current Stack Again
    while (stacksArray[currStack]->getLength() != stackLen)
    {
      // All Nodes have been Popped from Current Stack. Perform Last Iteration
      if (stacksArray[currStack]->getLength() == 0)
      {
        // Move Nodes from Stack at mainAuxIndex, through Stack at auxIndex, to Current Stack
        modHanoi(stackLen, mainAuxIndex, auxIndex, currStack, stacksArray, listsArray);

        // Update maxLength. MUST BE EQUAL TO maxLength
        maxLength = stacksArray[mainAuxIndex]->getLength();

        // Print Stacks
        printStacks(listsArray, maxLength);

        break;
      }

      // Get Current Stack Top Node's Value
      currStackTop = stacksArray[currStack]->top();

      // Current Stack Top Node's Value is Less than mainAux Stack Top Node's Value
      if ((currStackTop <= stacksArray[mainAuxIndex]->top()))
        // Move from Current Stack to Stack at mainAuxIndex
        moveAtoB(currStack, mainAuxIndex, stacksArray, listsArray);
      else
      {
        // Counter to Check at which Level Should be Placed the Disk
        int nDisks;

        // Only Compare Nodes that were Popped from Current Stack
        for (nDisks = 1; nDisks <= maxLength - stackLen; nDisks++)
          if (listsArray[mainAuxIndex]->get(-1 * nDisks) >= currStackTop)
            break;

        // Move nDisks from Stack at mainAuxIndex to Stack at auxIndex
        modHanoi(nDisks, mainAuxIndex, currStack, auxIndex, stacksArray, listsArray);

        // Move Current Stack Top Node to Stack at mainAuxIndex
        moveAtoB(currStack, mainAuxIndex, stacksArray, listsArray);

        // Move nDisks from Stack at auxIndex to Stack at mainAuxIndex
        modHanoi(nDisks, auxIndex, currStack, mainAuxIndex, stacksArray, listsArray);
      }

      // Update maxLength
      maxLength++;

      printStacks(listsArray, maxLength);
    };
  }

  // Deallocate Memory
  delete[] stacksArray;
  delete[] listsArray;
}

// --- Functions

// Function to Print Stacks
void printStacks(NumberDoublyPtr *listsArray, int maxLength)
{
  // Array Used to Check if the Given Stack has a Length Greater or Equal to Current Level
  bool greaterLength[stacks::nStacks];
  fill(greaterLength, greaterLength + stacks::nStacks, false);

  // Current Node Level that's being Printed from All Stacks that have that Length
  int currLevel = maxLength;

  cout << '\n';
  printTitle("Stacks");

  // Stacks Content
  ostringstream content;

  // Loop Over All Stack Levels
  for (; currLevel > 0; currLevel--)
  {
    // Print Stack Level which has a Length Equal or Greater than Current Level
    for (int n = 0; n < stacks::nStacks; n++)
    {
      // Check if Current Stack has a Length Equal or Geater than Current Level
      if (!greaterLength[n])
        greaterLength[n] = listsArray[n]->getLength() >= currLevel;

      if (n != 0)
        content << terminal::tab2;

      // Current Stack have less Nodes than Current Level
      if (!greaterLength[n])
      {
        content << string(stacks::maxDigits + 4, ' ');
        continue;
      }

      content << "| " << setw(stacks::maxDigits) << setfill(' ') << left << listsArray[n]->get(-1 * currLevel) << " |";
    }

    content << '\n';
  }

  // Print Content
  cout << content.str();
}