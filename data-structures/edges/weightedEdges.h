#include "../single-linked-lists/base.h"
#include "../queue/base.h"

#ifndef WEIGHTED_NODE_EDGES
#define WEIGHTED_NODE_EDGES

// WEIGHTED NODE CLASS
class WeightedNodeEdge
{
protected:
  int dstId;
  int weight;

public:
  // Constructors
  WeightedNodeEdge(int, int);

  // Public Methods
  int getWeight() { return this->weight; };
  int getDstId() { return this->dstId; };
};

// WeightedNodeEdgePtr Definition
using WeightedNodeEdgePtr = WeightedNodeEdge *;
using Edge = WeightedNodeEdgePtr;

// WEIGHTED NODE EDGES CLASS

class WeightedNodeEdges
{
private:
  int srcId;
  QueueLinkedList<Edge> *edges = NULL;

public:
  // Constructors
  WeightedNodeEdges(int, QueueLinkedList<Edge> *);
  WeightedNodeEdges(int, SingleLinkedList<Edge> *);

  // Destructor
  virtual ~WeightedNodeEdges()
  {
    // Deallocate Destinations Nodes ID
    for (int edgesLength = edges->getLength(); edgesLength > 0; edgesLength--)
      delete edges->dequeue();

    delete edges;
  }

  // Public Methods
  int getSrcId() { return this->srcId; };
  QueueLinkedList<Edge> *getEdges();
};

// WeightedNodeEdgesPtr Definition
using WeightedNodeEdgesPtr = WeightedNodeEdges *;
using Edges = WeightedNodeEdgesPtr;

// WEIGHTED NODE EDGE CLASS

// Weighted Node Edge Class Constructor
WeightedNodeEdge::WeightedNodeEdge(int dstId, int weight)
{
  this->dstId = dstId;
  this->weight = weight;
}

// WEIGHTED NODE EDGES CLASS

// Weighted Node Edges Class Constructors
WeightedNodeEdges::WeightedNodeEdges(int srcId, QueueLinkedList<Edge> *edges)
{
  Edge edge;

  // Intialize Edges Single Linked List
  this->edges = new QueueLinkedList<Edge>(NULL);

  // Set Edge's Source Node ID and Destinations Nodes ID, with its Corresponding Weights
  this->srcId = srcId;

  for (int edgesLength = edges->getLength(); edgesLength > 0; edgesLength--)
  {
    // Get Edge and Push it Back
    edge = edges->removeBack();

    // Add Edge
    this->edges->enqueue(new WeightedNodeEdge(edge->getDstId(), edge->getWeight()));
  }
}

WeightedNodeEdges::WeightedNodeEdges(int srcId, SingleLinkedList<Edge> *edges)
{
  Edge edge;

  // Intialize Edges Single Linked List
  this->edges = new QueueLinkedList<Edge>(NULL);

  // Set Edge's Source Node ID and Destinations Nodes ID, with its Corresponding Weights
  this->srcId = srcId;

  for (int edgesLength = edges->getLength(); edgesLength > 0; edgesLength--)
  {
    // Get Edge and Push it Back
    edge = edges->removeBack();

    // Add Edge
    this->edges->enqueue(new WeightedNodeEdge(edge->getDstId(), edge->getWeight()));
  }
}

// Getters

// Method to Get Destinations Nodes ID and its Corresponding Weights from the Given Node Source ID
QueueLinkedList<Edge> *WeightedNodeEdges::getEdges()
{
  Edge edge;

  // Initialize Queue Copy of Edges
  QueueLinkedList<Edge> *copyEdges = new QueueLinkedList<Edge>(NULL);

  // Create Queue Copy
  for (int edgeLength = this->edges->getLength(); edgeLength > 0; edgeLength--)
  {
    // Get Edge and Push it Back
    edge = this->edges->removeBack();

    // Insert Edge to the Deep Copy Queue
    copyEdges->enqueue(new WeightedNodeEdge(edge->getDstId(), edge->getWeight()));
  }

  return copyEdges;
}

#endif