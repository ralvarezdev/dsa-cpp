#include "../nodes/undirNode.h"
#include "../edges/weightedEdges.h"

#include <iostream>
using std::cout;

#ifndef UNDIR_GRAPHS
#define UNDIR_GRAPHS

// UNDIRECTED GRAPHS CLASS

template <class NodeType>
class UndirGraph
{
protected:
  SingleLinkedList<UndirNodePtr<NodeType>> *nodes = new SingleLinkedList<UndirNodePtr<NodeType>>(NULL);

  // DON'T MODIFY. THIS WILL BE USED AS INDEXES FOR THE SINGLE LINKED LIST
  int nodeIndex = 0;

public:
  // Constructors
  UndirGraph();

  // Destructor
  virtual ~UndirGraph()
  {
    UndirNodePtr<NodeType> node;

    // Get First Node
    while (!this->nodes->isEmpty())
    {
      node = this->nodes->remove();
      delete node;
    }
  }

  // Public Methods
  SingleLinkedList<int> *addNodes(QueueLinkedList<NodeType> *);
  void addEdges(QueueLinkedList<WeightedEdgePtr> *);
  SingleLinkedList<UndirNodePtr<NodeType>> *getNodesEdges();
};

// UndirGraphPtr Definition
template <class NodeType>
using UndirGraphPtr = UndirGraph<NodeType> *;

// Undirected Graph Constructors
template <class NodeType>
UndirGraph<NodeType>::UndirGraph()
{
  return;
}

// Method to Add Nodes to the Given Graph
template <class NodeType>
SingleLinkedList<int> *UndirGraph<NodeType>::addNodes(QueueLinkedList<NodeType> *nodesData)
{
  UndirNodePtr<NodeType> node;
  SingleLinkedList<int> *nodesIndexes = new SingleLinkedList<int>(-1);

  // Add Nodes
  while (!nodesData->isEmpty())
  {
    // Get Node's Data
    NodeType nodeData = nodesData->dequeue();

    // Store Node ID
    nodesIndexes->pushBack(this->nodeIndex);

    // Allocate Memory for the New Node and Insert It to the Graph
    node = new UndirNode<NodeType>(this->nodeIndex++, nodeData);
    this->nodes->push(node);
  }

  // Deallocate Memory
  delete nodesData;

  return nodesIndexes;
}

// Method to Add Edges to a Given Node
template <class NodeType>
void UndirGraph<NodeType>::addEdges(QueueLinkedList<WeightedEdgePtr> *edges)
{
  UndirNodePtr<NodeType> node;
  WeightedEdgePtr nodeEdges;
  int srcId;

  // Add Undirected Edges
  while (!edges->isEmpty())
  {
    // Get Edge and Edge's Source Node ID
    nodeEdges = edges->dequeue();
    srcId = nodeEdges->getSrcId();

    // Get Node at the Given Index
    node = this->nodes->get(srcId);

    // Insert Edges to the Node
    node->addEdges(nodeEdges->getDstsId());

    // Deallocate Memory
    delete nodeEdges;
  }

  // Deallocate Memory
  delete edges;
}

// Method to Get Nodes Edges
template <class NodeType>
SingleLinkedList<UndirNodePtr<NodeType>> *UndirGraph<NodeType>::getNodesEdges()
{
  UndirNodePtr<NodeType> node;
  int length = this->nodes->getLength();

  // Initialize Single Linked List Copy of Nodes Edges
  SingleLinkedList<UndirNodePtr<NodeType>> *copyNodes = new SingleLinkedList<UndirNodePtr<NodeType>>(NULL);

  // Create Single Linked List Copy
  while (length > 0)
  {
    node = this->nodes->remove();

    // Push Back Node Edge to the Deep Copy Single Linked List
    copyNodes->pushBack(node);

    // Push Data Back
    this->nodes->pushBack(node);
  }

  return copyNodes;
}

#endif