#include "../single-linked-lists/base.h"
#include "../single-linked-lists/number.h"
#include "../queue/base.h"

#ifndef WEIGHTED_NODE_EDGES
#define WEIGHTED_NODE_EDGES

// WEIGHTED EDGE CLASS

class WeightedNodeEdges
{
private:
  int srcId;
  QueueLinkedList<int> *dstsId = new QueueLinkedList<int>(-1);
  int weight;

public:
  // Constructors
  WeightedNodeEdges(int, int, QueueLinkedList<int> *);
  WeightedNodeEdges(int, int, NumberSingleLinkedList<int> *);

  // Destructor
  virtual ~WeightedNodeEdges()
  {
    // Deallocate Destinations Nodes ID
    delete dstsId;
  }

  // Public Methods
  int getSrcId();
  QueueLinkedList<int> *getDstsId();
};

// WeightedNodeEdgesPtr Definition
using WeightedNodeEdgesPtr = WeightedNodeEdges *;

// Weighted Edge Class Constructors
WeightedNodeEdges::WeightedNodeEdges(int weight, int srcId, QueueLinkedList<int> *dstsId)
{
  // Set Edge Weight and Edge's Source Node ID and Destinations Nodes ID
  this->weight = weight;
  this->srcId = srcId;

  while (!dstsId->isEmpty())
    this->dstsId->enqueue(dstsId->dequeue());

  // Deallocate Memory
  delete dstsId;
}

WeightedNodeEdges::WeightedNodeEdges(int weight, int srcId, NumberSingleLinkedList<int> *dstsId)
{
  // Set Edge Weight and Edge's Source Node ID and Destinations Nodes ID
  this->weight = weight;
  this->srcId = srcId;

  while (!dstsId->isEmpty())
    this->dstsId->enqueue(dstsId->pop());

  // Deallocate Memory
  delete dstsId;
}

// Getters

// Method to Get Edge's Source Node ID
int WeightedNodeEdges::getSrcId()
{
  return this->srcId;
}

// Method to Get Destinations Nodes ID from the Given Node Source ID
QueueLinkedList<int> *WeightedNodeEdges::getDstsId()
{
  int dstId;
  int length = this->dstsId->getLength();

  // Initialize Queue Copy of Destinations Nodes ID
  QueueLinkedList<int> *copyDstsId = new QueueLinkedList<int>(-1);

  // Create Queue Copy
  while (length > 0)
  {
    dstId = this->dstsId->dequeue();

    // Insert Edge to the Deep Copy Queue
    copyDstsId->enqueue(dstId);

    // Push Data Back
    this->dstsId->enqueue(dstId);
  }

  return copyDstsId;
}

#endif