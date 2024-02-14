#include "../../../../../data-structures/doubly-linked-lists/number.h"
#include "../../../../../data-structures/stack/number.h"

#ifndef MOD_HANOI_ALGORITHM
#define MOD_HANOI_ALGORITHM

// NumberDoublyPtr Definition
using NumberDoublyPtr = NumberDoublyLinkedList<int> *;

// NumberStackPtr Definition
using NumberStackPtr = NumberStackLinkedList<int> *;

// --- Function Prototypes
void modHanoi(int nDisks, int mainIndex, int auxIndex, int mainAuxIndex, NumberStackPtr *stacks, NumberDoublyPtr *lists);
void moveAtoB(int fromIndex, int toIndex, NumberStackPtr *stacks, NumberDoublyPtr *lists);

#endif