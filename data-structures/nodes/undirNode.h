#include "../single-linked-lists/base.h"
#include "../queue/base.h"

#ifndef UNDIR_NODE
#define UNDIR_NODE

// UNDIRECTED NODE CLASS
// Self-Referential Structure

template <class NodeType>
class UndirNode
{
public:
  NodeType *data;
  int nodeId = -1;
  SingleLinkedList<int> *edges = new SingleLinkedList<int>(-1);

  // Constructors
  UndirNode();
  UndirNode(int, NodeType *);

  // Destructor
  virtual ~UndirNode()
  {
    // Deallocate Node's Data and Single Linked List that Contains Node's Edges Information
    delete this->data;
    delete this->edges;
  }

  // Public Methods
  void addEdges(QueueLinkedList<int> *);
};

// UndirNodePtr Definition
template <class NodeType>
using UndirNodePtr = UndirNode<NodeType> *;

// Node Class Constructors
template <class NodeType>
UndirNode<NodeType>::UndirNode()
{
  return;
}

template <class NodeType>
UndirNode<NodeType>::UndirNode(int nodeId, NodeType *data)
{
  // Set Node Data
  this->nodeId = nodeId;
  this->data = data;
}

// Method to Add Edges to the Node
template <class NodeType>
void UndirNode<NodeType>::addEdges(QueueLinkedList<int> *queue)
{
  // Set Node Edges
  while (!queue->isEmpty())
    this->edges->push(queue->dequeue());

  // Deallocate Memory
  delete queue;
}

#endif
