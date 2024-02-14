#include "modHanoi.h"

// --- Functions Prototypes
void modHanoi(int nDisks, int mainIndex, int auxIndex, int mainAuxIndex, NumberStackPtr *stacks, NumberDoublyPtr *lists);

// --- Functions

// Modified Version of Hanoi Solution Algorithm, Adapted to this Practice Problem
// A: mainIndex, B: auxIndex, C: mainAuxIndex
void modHanoi(int nDisks, int mainIndex, int auxIndex, int mainAuxIndex, NumberStackPtr *stacks, NumberDoublyPtr *lists)
{
  if (nDisks > 0)
  {
    modHanoi(nDisks - 1, mainIndex, mainAuxIndex, auxIndex, stacks, lists);

    // Move Last Node from A to C

    // Pop Last Node from Stack and Doubly Linked List at mainIndex
    int number = stacks[mainIndex]->pop();
    lists[mainIndex]->pop();

    // Push Node to Stack and Doubly Linked List at mainAuxIndex
    stacks[mainAuxIndex]->push(number);
    lists[mainAuxIndex]->push(number);

    modHanoi(nDisks - 1, auxIndex, mainIndex, mainAuxIndex, stacks, lists);
  }
}