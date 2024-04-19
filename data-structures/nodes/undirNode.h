#include "../edges/weightedEdges.h"
#include "../single-linked-lists/base.h"
#include "../queue/base.h"

#ifndef UNDIR_NODE
#define UNDIR_NODE

// UNDIRECTED NODE CLASS

template <class NodeType>
class UndirNode
{
protected:
  NodeType data;
  int nodeId = -1;
  SingleLinkedList<Edge> *edges = new SingleLinkedList<Edge>(NULL);

public:
  // Constructors
  UndirNode();
  UndirNode(int, NodeType);

  // Destructor
  virtual ~UndirNode()
  {
    Edge edge;
    int edgesLength = edges->getLength();

    // Deallocate Node's Data and Single Linked List that Contains Node's Edges Information
    while (edgesLength > 0)
    {
      edge = edges->remove();

      edgesLength--;
      delete edge;
    }
    delete this->edges;
  }

  // Public Methods
  void addEdges(QueueLinkedList<Edge> *);
  NodeType getData() { return this->data; };
  int getSrcId() { return this->nodeId; };
  SingleLinkedList<Edge> *getEdges();
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
UndirNode<NodeType>::UndirNode(int nodeId, NodeType data)
{
  // Set Node Data
  this->nodeId = nodeId;
  this->data = data;
}

// Method to Add Edges to the Node
template <class NodeType>
void UndirNode<NodeType>::addEdges(QueueLinkedList<Edge> *edges)
{
  Edge edge;
  int edgesLength = edges->getLength();

  // Set Node Edges
  while (edgesLength > 0)
  {
    // Get Edge and Push it Back
    edge = edges->removeBack();

    // Add Edge
    this->edges->push(new WeightedNodeEdge(edge->getDstId(), edge->getWeight()));

    edgesLength--;
  }
}

// Method to Get Destinations Nodes ID and its Corresponding Weights
template <class NodeType>
SingleLinkedList<Edge> *UndirNode<NodeType>::getEdges()
{
  Edge edge;
  int edgesLength = edges->getLength();

  // Initialize Single Linked List Copy of Edges
  SingleLinkedList<Edge> *copyEdges = new SingleLinkedList<Edge>(NULL);

  // Set Node Edges
  while (edgesLength > 0)
  {
    // Get Edge and Push it Back
    edge = this->edges->removeBack();

    // Insert Edge to the Deep Copy Linked List
    copyEdges->push(new WeightedNodeEdge(edge->getDstId(), edge->getWeight()));

    edgesLength--;
  }

  return copyEdges;
}

#endif
