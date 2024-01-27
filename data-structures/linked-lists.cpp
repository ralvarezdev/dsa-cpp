#include <iostream>
#include <string>
#include <cstdlib>

using std::cout;
using std::string;

// NODE STRUCT
// Self-Referential Structure

struct Node
{
  int num;
  Node *next = NULL;
};

typedef Node *NodePtr;

// LINKED LIST CLASS
class LinkedList
{
private:
  NodePtr head;
  NodePtr curr;
  int length = 0;

  // Private Methods
  void increaseLength();
  void decreaseLength();
  void setCurrent(NodePtr);

public:
  // Constructors
  LinkedList();
  LinkedList(int);
  LinkedList(int[], int);
  ~LinkedList();

  // Public Methods
  bool isEmpty();
  int removeFirst();
  void print();
  void printReverse();
  int getLength();
  void setHeadAsCurrent();
  int total();
};

// Linked List Constructors

// Add Head with Next Node as NULL
LinkedList::LinkedList()
{
  NodePtr p = new Node();

  // Add Node as Head
  this->head = p;

  // Set Head as Current Node
  this->setHeadAsCurrent();
}

// Add Head with Only One Next Node
LinkedList::LinkedList(int num)
{
  NodePtr p = new Node();

  // Add Node as Head
  this->head = p;

  // Add Next Node
  p = new Node();
  p->num = num;
  this->head->next = p;

  // Increase Length
  this->increaseLength();

  // Set Head as Current Node
  this->setHeadAsCurrent();
}

// Add Head and Multiple Next Nodes
LinkedList::LinkedList(int nums[], int length)
{
  NodePtr p = new Node();

  // Add Node to Head
  this->head = p;

  // Set Head as Current Node
  this->curr = this->head;

  // Add Next Nodes
  for (int i = 0; i < length; i++)
  {
    p = new Node();
    p->num = nums[i];

    // Add Node
    this->curr->next = p;

    // Set Current Node
    this->curr = this->curr->next;

    // Increase Length
    this->increaseLength();
  }

  // Set Head as Current Node
  this->setHeadAsCurrent();
}

// Destructor
LinkedList::~LinkedList()
{
  // Remove Node Next to Head if It isn't Empty
  while (!isEmpty())
    this->removeFirst();

  // Remove Head Node
  NodePtr temp = this->head;
  this->head = NULL;

  delete[] temp;
}

// Method to Remove Node Next to Head
int LinkedList::removeFirst()
{
  if (this->isEmpty())
    return -1;

  NodePtr temp = this->head->next;
  int item = temp->num;

  head->next = temp->next;

  delete[] temp;
  decreaseLength();

  return item;
}

// Method to Check if Linked List is Empty
bool LinkedList::isEmpty()
{
  return this->head->next == NULL;
}

// Method to Increase Linked List Length
void LinkedList::increaseLength()
{
  this->length = this->length + 1;
}

// Method to Decrease Linked List Length
void LinkedList::decreaseLength()
{
  this->length = this->length - 1;
}

// Method to Set Current Node
void LinkedList::setCurrent(NodePtr p)
{
  this->curr = p;
}

// Method to Set Head as Current Node
void LinkedList::setHeadAsCurrent()
{
  this->curr = this->head;
}

// Print Nodes Method
void LinkedList::print()
{
  NodePtr p = this->curr->next;

  // Prints from Head to Tail
  while (p != NULL)
  {
    cout << p->num << '\n';
    p = p->next;
  }
}

// Print Nodes with a Recursive Method
void LinkedList::printReverse()
{
  NodePtr p = this->curr;

  // Prints from Tail to Head
  if (p->next != NULL)
  {
    p = p->next;
    this->curr = p;
    this->printReverse();
    cout << p->num << '\n';
  }

  // NOTE: If the Print Statement is before the Recursive Function Call, Nodes will be Printed from Head to Tail
}

/*
// Count Nodes with a Recursive Method
int LinkedList::count(NodePtr p)
{
  if (p != NULL)
    return count(p->next) + 1;

  return 0;
}
*/

// Method to Get Linked List Length
int LinkedList::getLength()
{
  return this->length;
}

// Method that Returns the Sum of All Node's Data Field
int LinkedList::total()
{
  NodePtr p = this->curr;
  int sum = 0;

  while (p != NULL)
  {
    sum += p->num;
    p = p->next;
  }

  return sum;
}

int main()
{
  // Memory Allocation
  int numbers[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};

  // LinkedList list = LinkedList();
  // LinkedList list = LinkedList(1);
  LinkedList list = LinkedList(numbers, 10);

  // Check if it's Empty
  string isEmpty = list.isEmpty() ? "True" : "False";
  cout << "Is Empty? " << isEmpty << "\n\n";

  // Check List Length
  int length = list.getLength();
  cout << "List Length: " << length << "\n\n";

  // Get Total
  int total = list.total();
  cout << "List Total: " << total << "\n\n";

  // Print Nodes
  cout << "Nodes:\n";
  list.print();

  cout << "\nFirst Node Removed:\n";
  list.removeFirst();
  list.print();

  cout << "\nNodes (Reverse):\n";
  list.printReverse();
}