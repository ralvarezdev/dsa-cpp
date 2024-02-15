#include "modHanoi.h"

// --- Functions Prototypes
void modHanoi(int nDisks, int mainIndex, int auxIndex, int mainAuxIndex, NumberStackPtr *stacks, NumberDoublyPtr *lists);
void moveAtoB(int fromIndex, int toIndex, NumberStackPtr *stacks, NumberDoublyPtr *lists);

// --- Functions

// Modified Version of Hanoi Solution Algorithm, Adapted to this Practice Problem
// A: mainIndex, B: auxIndex, C: mainAuxIndex
void modHanoi(int nDisks, int mainIndex, int auxIndex, int mainAuxIndex, NumberStackPtr *stacks, NumberDoublyPtr *lists)
{
  if (nDisks > 0)
  {
    // Move Last Node from A to B
    modHanoi(nDisks - 1, mainIndex, mainAuxIndex, auxIndex, stacks, lists);

    // Move Last Node from A to C
    moveAtoB(mainIndex, mainAuxIndex, stacks, lists);

    // Move Last Node from B to C
    modHanoi(nDisks - 1, auxIndex, mainIndex, mainAuxIndex, stacks, lists);
  }
}

// Function to Move Top Node from A Stack to B Stack
void moveAtoB(int fromIndex, int toIndex, NumberStackPtr *stacks, NumberDoublyPtr *lists)
{
  // Remove Top Node from Current Stack
  int number = stacks[fromIndex]->pop();
  lists[fromIndex]->remove();

  // Push Top Node from Current Stack to Stack at mainAuxIndex
  stacks[toIndex]->push(number);
  lists[toIndex]->push(number);

  // Print Stack at toIndex Top Node
  // cout << "Top Node at Stack " << toIndex + 1 << ": " << number << '\n';
}