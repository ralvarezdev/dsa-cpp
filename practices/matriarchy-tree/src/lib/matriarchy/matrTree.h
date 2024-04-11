#include "../../../../../data-structures/queue/base.h"
#include "matrNode.h"

#ifndef MATR_TREE
#define MATR_TREE

// MATRIARCHY TREE CLASS

class MatrTree
{
protected:
  MatrNodePtr root = NULL;

public:
  // Constructors
  MatrTree(){};

  // Destructor
  virtual ~MatrTree()
  {
    MatrNodePtr n, children[3];

    // Initialize Queue that will Store All the Nodes whose Memory will be Deallocated
    QueueLinkedList<MatrNodePtr> *nodes = new QueueLinkedList<MatrNodePtr>(NULL);

    // Get Root Node
    n = this->root;
    nodes->push(n);

    while (!nodes->isEmpty())
    {
      // Get First Node
      n = nodes->dequeue();

      // Get n's Children
      children[0] = n->lChild;
      children[1] = n->mChild;
      children[2] = n->rChild;

      for (int i = 0; i < 3; i++)
      {
        // Check if the Child Exists
        if (children[i] == NULL)
          continue;

        // Set Mother Attribute as NULL
        children[i]->mother = NULL;

        // Push n's Child
        nodes->enqueue(children[i]);
      }

      // Deallocate Parent Node
      delete n;
    }

    // Deallocate Memory
    delete nodes;
  }

  // Public Methods
  // void readFile()
};

#endif