#include "base.h"

#ifndef NUMBER_STACK_LINKED_LISTS
#define NUMBER_STACK_LINKED_LISTS

// NUMBER STACK LINKED LIST CLASS

template <class NodeType>
class NumberStackLinkedList : public StackLinkedList<NodeType>
{
public:
  // Inherit Constructors
  using StackLinkedList<NodeType>::StackLinkedList;

  // Constructors
  NumberStackLinkedList() : StackLinkedList<NodeType>(-1){};
};

#endif