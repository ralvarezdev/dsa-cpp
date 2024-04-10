#include <iostream>
#include <iomanip>
#include <sstream>

#include "../../../../../data-structures/queue/base.h"
#include "../terminal/cols.h"
#include "../namespaces.h"

using std::cout;
using std::ostringstream;
using std::setfill;
using std::setw;

using namespace terminal;
using namespace matrPerson;

#ifndef MATR_NODE
#define MATR_NODE

// MATRIARCHY PERSON CLASS

class MatrPerson
{
private:
  int nodeId;
  string name;
  bool consanguinity;
  matrPerson::genders gender = matrPerson::genders::genderNull;
  MatrPerson *partner = NULL;

public:
  // Constructors
  MatrPerson(int, string, bool, matrPerson::genders, MatrPerson *);

  // Public Methods
  int getNodeId();
  string getName();
  bool getConsanguinity();
  matrPerson::genders getGender();
  MatrPerson *getPartner();
};

// MATRIARCHY NODE CLASS
// Self-Referential Structure

class MatrNode
{
protected:
  // Protected Methods
  void MatrNode::addRootHeaderToStream(ostringstream *);
  void MatrNode::addRootDataToStream(ostringstream *, int, MatrPerson *);
  void MatrNode::addChildHeaderToStream(ostringstream *);
  void MatrNode::addChildDataToStream(ostringstream *, int, int, MatrPerson *);

  void levelOrder(MatrNodePtr, matrPerson::traversals);
  void levelOrderParents(int, QueueLinkedList<MatrNodePtr> *, ostringstream *);
  void levelOrderWomen(int, QueueLinkedList<MatrNodePtr> *, ostringstream *);
  void levelOrderMen(int, QueueLinkedList<MatrNodePtr> *, ostringstream *);
  void levelOrderSingle(int, QueueLinkedList<MatrNodePtr> *, ostringstream *);

public:
  MatrPerson *data;
  MatrNode *lChild = NULL; // Left Child
  MatrNode *mChild = NULL; // Middle Child
  MatrNode *rChild = NULL; // Right Child

  // Inherit Constructors

  // Public Methods
  void levelOrderParents() { this->levelOrder(this, matrPerson::parents); };
  void levelOrderWomen() { this->levelOrder(this, matrPerson::women); };
  void levelOrderMen() { this->levelOrder(this, matrPerson::men); };
  void levelOrderSingle() { this->levelOrder(this, matrPerson::single); };
};

// MatrNodePtr Definition
using MatrNodePtr = MatrNode *;

// MARTIARCHY PERSON CLASS

// Matriarchy Person Class Constructor
MatrPerson::MatrPerson(int nodeId, string name, bool consanguinity, matrPerson::genders gender, MatrPerson *partner = NULL)
{
  // Assign Data
  this->nodeId = nodeId;
  this->consanguinity = consanguinity;
  this->name = name;
  this->gender = gender;
  this->partner = partner;
}

// Getters

// Method to Get Node ID
int MatrPerson::getNodeId()
{
  return this->nodeId;
}

// Method to Get Name
string MatrPerson::getName()
{
  return this->name;
}

// Method to Check whether the Person is Part of the Tree by Consanguinity or Affinity
bool MatrPerson::getConsanguinity()
{
  return this->consanguinity;
}

// Method to Get Gender
matrPerson::genders MatrPerson::getGender()
{
  return this->gender;
}

// Method to Get the Partner Information (It's a Matriarchy Tree...)
MatrPerson *MatrPerson::getPartner()
{
  return this->partner;
}

// MATRIARCHY NODE CLASS

// Method to Add Root Node Header to a Given Stringstream
void MatrNode::addRootHeaderToStream(ostringstream *msg)
{
  // Root Header
  Col cols[3] = {
      Col("Root Mother", terminal::nNodeId),
      Col("Name", terminal::nName),
      Col("Partner", terminal::nName)};

  // Create Title Linked List
  ColLinkedList *titleList = new ColLinkedList(cols, 3, Col());

  *msg << titleList->getText() << '\n';

  // Deallocate Memory
  delete titleList;
}

// Method to Add Root Node Data to a Given Stringstream
void MatrNode::addRootDataToStream(ostringstream *msg, int level, MatrPerson *root)
{
  // Get Root Node Partner
  MatrPerson *partner = root->getPartner();

  // Add Root Node Data
  *msg << setw(terminal::nLevel) << setfill(' ') << level
       << setw(terminal::nNodeId) << setfill(' ') << root->getNodeId()
       << setw(terminal::nName) << setfill(' ') << root->getName();

  if (partner != NULL)
    *msg << setw(terminal::nName) << setfill(' ') << partner->getName();
  *msg << '\n';
}

// Method to Add Child Nodes Header to a Given Stringstream
void MatrNode::addChildHeaderToStream(ostringstream *msg)
{
  // Node Header
  Col cols[7] = {
      Col("Mother Node", terminal::nMotherId),
      Col("Node", terminal::nNodeId),
      Col("Name", terminal::nName),
      Col("Gender", terminal::nGender),
      Col("Status", terminal::nStatus),
      Col("Consanguinity", terminal::nConsanguinity),
      Col("Partner", terminal::nName)};

  // Create Title Linked List
  ColLinkedList *titleList = new ColLinkedList(cols, 7, Col());

  // Add Node Header
  *msg << titleList->getText() << '\n';

  // Deallocate Memory
  delete titleList;
}

// Method to Add Child Node Data to a Given Stringstream
void MatrNode::addChildDataToStream(ostringstream *msg, int motherId, int level, MatrPerson *person)
{
  int status, consanguinity;
  string partnerName;
  matrPerson::genders gender;

  // Get Genders
  gender = person->getGender();

  // Get Status
  if (gender == matrPerson::man)
  {
    status = matrPerson::single;
    consanguinity = matrPerson::consanguinityAbbr;
    partnerName = "";
  }

  else
  {
    MatrPerson *partner = person->getPartner();
    status = (partner != NULL) ? matrPerson::marriedAbbr : matrPerson::singleAbbr;
    consanguinity = (person->getConsanguinity()) ? matrPerson::consanguinityAbbr : matrPerson::affinityAbbr;
    partnerName = (partner != NULL) ? partner->getName() : "";
  }

  // Add Child Node Data
  *msg << setw(terminal::nLevel) << setfill(' ') << level
       << setw(terminal::nMotherId) << setfill(' ') << motherId
       << setw(terminal::nNodeId) << setfill(' ') << person->getNodeId()
       << setw(terminal::nGender) << setfill(' ') << gender
       << setw(terminal::nName) << setfill(' ') << person->getName()
       << setw(terminal::nStatus) << setfill(' ') << status
       << setw(terminal::nConsanguinity) << setfill(' ') << consanguinity
       << setw(terminal::nName) << setfill(' ') << partnerName << '\n';
}

// Method to Print the Nodes through Different Types of Level Order Traversal
void MatrNode::levelOrder(MatrNodePtr n, matrPerson::traversals traversal)
{
  int level;
  MatrPerson *child;
  ostringstream msg;

  QueueLinkedList<MatrNodePtr> *nodes = new QueueLinkedList<MatrNodePtr>(NULL);

  // Push Node to Queue
  nodes->push(n);
  level = 0;

  // Add Root Header to Stream
  this->addRootHeaderToStream(&msg);

  // Add Root Node Data to Stream
  this->addRootDataToStream(&msg, level, n->data);
  msg << '\n';

  // Add Nodes Child Header to Stream
  this->addChildHeaderToStream(&msg);

  // Traverse the Matriarchy Tree
  switch (traversal)
  {
  case matrPerson::parents:
    this->levelOrderParents(level, nodes, &msg);
    break;
  }

  // Print Level Order Traversal
  cout << msg.str();

  // Deallocate Memory
  delete nodes;
}

// Method to Add the Parent-Child Relationship to a Given Stringstream
void MatrNode::levelOrderParents(int level, QueueLinkedList<MatrNodePtr> *nodes, ostringstream *msg)
{
  int nextNodesLevel, currNodesLevel, nId;
  MatrNodePtr n, children[3];
  MatrPerson *child;

  nextNodesLevel = 1;
  level = currNodesLevel = 0;

  while (!nodes->isEmpty())
  {
    // Get the Number of Nodes in the Current Tree Level. Increase the Level Counter
    if (currNodesLevel == 0)
    {
      currNodesLevel = nextNodesLevel;
      nextNodesLevel = 0;
      level++;
    }

    // Get First Node
    n = nodes->dequeue();
    nId = n->data->getNodeId();

    // Get n's Children
    children[0] = n->lChild;
    children[1] = n->mChild;
    children[2] = n->rChild;

    for (int i = 0; i < 3; i++)
    {
      // Get Child Data
      child = children[1]->data;

      // Add Child Data to Stream
      this->addChildDataToStream(msg, nId, level, child);

      // Push n's Child
      nodes->enqueue(children[i]);

      // Increase the Next Level Nodes Counter
      nextNodesLevel++;
    }

    // Decrease the Number of Nodes on the Current Level
    currNodesLevel--;
  }
}

// Method to Print Only Women through Level Order Traversal
void MatrNode::levelOrderWomen(int level, QueueLinkedList<MatrNodePtr> *nodes, ostringstream *msg)
{
  int nextNodesLevel, currNodesLevel, nId;
  MatrNodePtr n, children[3];
  MatrPerson *child;

  nextNodesLevel = 1;
  level = currNodesLevel = 0;

  while (!nodes->isEmpty())
  {
    // Get the Number of Nodes in the Current Tree Level. Increase the Level Counter
    if (currNodesLevel == 0)
    {
      currNodesLevel = nextNodesLevel;
      nextNodesLevel = 0;
      level++;
    }

    // Get First Node
    n = nodes->dequeue();
    nId = n->data->getNodeId();

    // Get n's Children
    children[0] = n->lChild;
    children[1] = n->mChild;
    children[2] = n->rChild;

    for (int i = 0; i < 3; i++)
    {
      // Get Child Data
      child = children[i]->data;

      // Check if It's a Woman
      if (child->getGender() == matrPerson::woman)
        // Add Child Data to Stream
        this->addChildDataToStream(msg, nId, level, child);

      // Push n's Child
      nodes->enqueue(children[i]);

      // Increase the Next Level Nodes Counter
      nextNodesLevel++;
    }

    // Decrease the Number of Nodes on the Current Level
    currNodesLevel--;
  }
}

// Method to Print Only Men through Level Order Traversal
void MatrNode::levelOrderMen(int level, QueueLinkedList<MatrNodePtr> *nodes, ostringstream *msg)
{
  int nextNodesLevel, currNodesLevel, nId;
  MatrNodePtr n, children[3];
  MatrPerson *child, *partner;

  nextNodesLevel = 1;
  level = currNodesLevel = 0;

  while (!nodes->isEmpty())
  {
    // Get the Number of Nodes in the Current Tree Level. Increase the Level Counter
    if (currNodesLevel == 0)
    {
      currNodesLevel = nextNodesLevel;
      nextNodesLevel = 0;
      level++;
    }

    // Get First Node
    n = nodes->dequeue();
    nId = n->data->getNodeId();

    // Get n's Children
    children[0] = n->lChild;
    children[1] = n->mChild;
    children[2] = n->rChild;

    for (int i = 0; i < 3; i++)
    {
      // Get Child Data
      child = children[i]->data;
      partner = child->getPartner();

      // Check if It's a Man
      if (child->getGender() == matrPerson::man)
        // Add Child Data to Stream
        this->addChildDataToStream(msg, nId, level, child);

      // Check if It's a Woman and if She's Married
      else if (child->getGender() == matrPerson::woman && partner != NULL)
        // Add Woman's Partner Data to Stream
        this->addChildDataToStream(msg, nId, level, partner);

      // Push n's Child
      nodes->enqueue(children[i]);

      // Increase the Next Level Nodes Counter
      nextNodesLevel++;
    }

    // Decrease the Number of Nodes on the Current Level
    currNodesLevel--;
  }
}

// Method to Print Only Single Nodes through Level Order Traversal
void MatrNode::levelOrderSingle(int level, QueueLinkedList<MatrNodePtr> *nodes, ostringstream *msg)
{
  int nextNodesLevel, currNodesLevel, nId;
  MatrNodePtr n, children[3];
  MatrPerson *child, *partner;

  nextNodesLevel = 1;
  level = currNodesLevel = 0;

  while (!nodes->isEmpty())
  {
    // Get the Number of Nodes in the Current Tree Level. Increase the Level Counter
    if (currNodesLevel == 0)
    {
      currNodesLevel = nextNodesLevel;
      nextNodesLevel = 0;
      level++;
    }

    // Get First Node
    n = nodes->dequeue();
    nId = n->data->getNodeId();

    // Get n's Children
    children[0] = n->lChild;
    children[1] = n->mChild;
    children[2] = n->rChild;

    for (int i = 0; i < 3; i++)
    {
      // Get Child Data
      child = children[i]->data;

      // Check if It's a Man
      if (child->getGender() == matrPerson::man)
        // Add Child Data to Stream
        this->addChildDataToStream(msg, nId, level, child);

      // Check if It's a Woman and have no kids
      else if (child->getGender() == matrPerson::woman)
        if (children[i]->lChild == NULL && children[i]->mChild == NULL && children[i]->rChild == NULL)
          // Add Woman's Partner Data to Stream
          this->addChildDataToStream(msg, nId, level, partner);

      // Push n's Child
      nodes->enqueue(children[i]);

      // Increase the Next Level Nodes Counter
      nextNodesLevel++;
    }

    // Decrease the Number of Nodes on the Current Level
    currNodesLevel--;
  }
}

#endif