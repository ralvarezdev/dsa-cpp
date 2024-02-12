#include <string>
#include <iostream>

#include "lib/terminal/ansiEsc.h"
#include "lib/terminal/input.h"
#include "../../../data-structures/stack/base.h"
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

using namespace std;

// --- Function Prototypes
void helpMessage();

int main(int argc, char **argv)
{
  // Desynchronize C++ Streams from C I/O Operations to Increase Performance
  std::ios::sync_with_stdio(false);

  // Print Title
  printTitle("SORTING STACKS PROBLEM", false);
  cout << '\n';

  // Ask for Number of Stacks to Create
  const int numberStacks = getInteger("Enter the Number of Stacks", 3, 6);

  // Ask for Number of Nodes for each Stack
  const int stackLength = getInteger("Enter the Number of Nodes for each Stack", 3, 10);
}