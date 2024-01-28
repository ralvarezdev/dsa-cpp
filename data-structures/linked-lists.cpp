#include <iostream>
#include <string>
#include <limits.h>
#include <cstdlib>
#include <iomanip>

using std::cout;
using std::left;
using std::setfill;
using std::setw;
using std::string;

// NODE STRUCT
// Self-Referential Structure

class Node
{
public:
  int num;
  Node *next = NULL;

  // Constructor
  Node();
  Node(int);
  Node(int, Node *);
};

// Node Class Constructors
Node::Node()
{
  return;
}

Node::Node(int num)
{
  this->num = num;
}

Node::Node(int num, Node *next)
{
  this->num = num;
  this->next = next;
}

typedef Node *NodePtr;

// LINKED LIST CLASS
class LinkedList
{
private:
  NodePtr head;
  NodePtr tail;
  NodePtr curr;

  int length = 0;

  // Private Methods
  void increaseLength();
  void increaseLength(int);
  void decreaseLength();
  void setCurrent(NodePtr);
  NodePtr move(NodePtr, int);

public:
  // Constructors
  LinkedList();
  LinkedList(int);
  LinkedList(int[], int);
  ~LinkedList();

  // Public Methods
  bool isEmpty();
  void insert(int);
  void push_back(int);
  void insertAt(int, int);
  int remove();
  int pop();
  int removeAt(int);
  int change(int, int);
  int get(int);
  void print();
  void print(NodePtr);
  void printReverse();
  void printReverse(NodePtr);
  int getLength();
  void setHeadAsCurrent();
  int total();
  int total(NodePtr);
  int max();
  int max(NodePtr);
  NodePtr linearSearch(int);
  NodePtr linearSearch(NodePtr, int);
};

// Linked List Constructors

// Add Head with Next Node as NULL
LinkedList::LinkedList()
{
  NodePtr p;

  // Add Node as Head and Tail
  this->head = this->tail = p = new Node();

  // Set Head as Current Node
  this->setHeadAsCurrent();
}

// Add Head with Only One Next Node
LinkedList::LinkedList(int num)
{
  NodePtr p;

  // Add Head
  this->head = p = new Node();

  // Add Next Node
  p = new Node(num);

  // Add Node as Head Next Node and as Tail
  this->tail = this->head->next = p;

  // Increase Length
  this->increaseLength();

  // Set Head as Current Node
  this->setHeadAsCurrent();
}

// Add Head and Multiple Next Nodes
LinkedList::LinkedList(int nums[], int length)
{
  NodePtr p;

  // Add Head
  this->head = p = new Node();

  // Add Node to Head and Set Head as Current Node
  this->curr = this->head;

  // Add Next Nodes
  for (int i = 0; i < length; i++)
  {
    // Add Node
    this->curr->next = p = new Node(nums[i]);

    // Set as Current Node
    this->curr = this->curr->next;
  }

  // Set p Node as Tail
  this->tail = p;

  // Increase Length
  this->increaseLength(length);

  // Set Head as Current Node
  this->setHeadAsCurrent();
}

// Destructor
LinkedList::~LinkedList()
{
  // Remove Node Next to Head if It isn't Empty
  while (!isEmpty())
    this->remove();

  // Remove Head Node
  NodePtr temp = this->head;
  this->head = NULL;

  delete[] temp;
}

// Method to Move to Next Node N Times
NodePtr LinkedList::move(NodePtr p, int n)
{
  // Move to Next N Nodes
  for (int i = 0; i < n; i++)
  {
    // Check if Next Node is NULL
    if (p->next == NULL)
      return NULL;

    p = p->next;
  }
  return p;
}

// Method to Insert Node Next to Head
void LinkedList::insert(int num)
{
  NodePtr n, p;

  // Get Node Next to Head
  n = this->head->next;
  p = new Node(num, n);

  // Set Node Next to Head
  this->head->next = p;

  this->increaseLength();
}

// Method to Insert Node at Given Position
void LinkedList::insertAt(int num, int pos)
{
  // Check pos
  if (pos == 0)
  {
    this->insert(num); // Insert Node Next to Head
    return;
  }

  if (pos < 0)
    pos = this->length + pos + 1; // Get Position

  if (pos >= this->length)
  {
    this->push_back(num); // Insert Node at Tail
    return;
  }

  NodePtr m, q, p;

  // Get Head
  m = this->head;

  // Move to Next Node pos Times
  m = this->move(m, pos);

  // pos is Out of Range
  if (m == NULL)
    return;

  // Perform Last Node Move
  p = m;
  m = m->next;

  // Create New Node and Set m as Next Node
  q = new Node(num, m);

  // Set Node at Given Position
  p->next = q;

  this->increaseLength();
}

// Method to Insert Node at Tail
void LinkedList::push_back(int num)
{
  NodePtr p = new Node(num);

  // Set Node at Tail
  this->tail->next = p;

  // Set Tail
  this->tail = p;

  this->increaseLength();
}

// Method to Remove Node Next to Head
int LinkedList::remove()
{
  if (this->isEmpty())
    return -1;

  // Get Node Next to Head
  NodePtr n = this->head->next;
  int num = n->num;

  // Remove n Node from Linked List
  head->next = n->next;

  // Deallocate Memory
  delete[] n;

  decreaseLength();

  return num;
}

// Method to Remove Node at Tail
int LinkedList::pop()
{
  if (this->isEmpty())
    return -1;

  NodePtr t, p;

  this->decreaseLength();

  // Move to Tail Previous Node
  p = this->move(this->head, this->length);

  // Get Tail
  t = p->next;
  int num = t->num;
  p->next = NULL;

  // Set Previous Node as Tail
  this->tail = p;

  // Deallocate Memory
  delete[] t;

  return num;
}

// Method to Remove Node at Given Index
int LinkedList::removeAt(int pos)
{
  // Check pos
  if (pos == 0)
    return this->remove(); // Remove Node Next to Head

  if (pos < 0)
    pos = this->length + pos; // Get Position

  if (pos > this->length)
    return -1; // Node not Found

  if (pos == this->length)
    return this->pop(); // Remove Tail

  NodePtr m, p, q;

  this->decreaseLength();

  // Move to Next Node pos Times
  m = this->move(this->head, pos);

  // pos is Out of Range
  if (m == NULL)
    return -1;

  // Perform Last Node Move
  p = m;
  m = m->next;

  // Remove Node
  q = m->next;
  int num = m->num;
  p->next = q;

  // Deallocate Memory
  delete[] m;

  return num;
}

// Method to Modify Node Value at Given Position
int LinkedList::change(int num, int pos)
{
  NodePtr n;
  int old;

  if (pos == 0)
  {
    old = this->head->next->num;
    this->head->next->num = num; // Change Value to Node Next to Head
    return old;
  }

  if (pos < 0)
    pos = this->length + pos; // Get Position
  pos += 1;

  if (pos > this->length)
    return -1; // Node not Found

  if (pos == this->length)
  {
    old = this->tail->num;
    this->tail->num = num; // Change Value to Tail
    return old;
  }

  if (this->isEmpty())
    return -1;

  // Set Head to n
  n = this->head;

  // Move to Node
  n = this->move(n, pos);

  // pos is Out of Range
  if (n == NULL)
    return -1;

  // Assign New Value
  old = n->num;
  n->num = num;

  return num;
}

// Method to Get Node at Given Position
int LinkedList::get(int pos)
{
  // Check pos
  if (pos == 0)
    return this->head->next->num; // Get Node Next to Head

  if (pos < 0)
    pos = this->length + pos; // Get Position
  pos += 1;

  if (pos > this->length)
    return -1; // Node not Found

  if (pos == this->length)
    return this->tail->num; // Get Tail

  if (this->isEmpty())
    return -1;

  NodePtr n;

  n = this->head;

  // Move to Node
  n = this->move(n, pos);

  // pos is Out of Range
  if (n == NULL)
    return -1;

  // Return Value
  return n->num;
}

// Method to Check if Linked List is Empty
bool LinkedList::isEmpty()
{
  return this->head->next == NULL;
}

// Method to Increase Linked List Length
void LinkedList::increaseLength()
{
  this->length += 1;
}

void LinkedList::increaseLength(int length)
{
  this->length += length;
}

// Method to Decrease Linked List Length
void LinkedList::decreaseLength()
{
  this->length -= 1;
}

// Method to Set Current Node
void LinkedList::setCurrent(NodePtr p)
{
  this->curr = p;
}

// Method to Set Head Node as Current Node
void LinkedList::setHeadAsCurrent()
{
  this->curr = this->head;
}

// Print Nodes Method from Head to Tail
void LinkedList::print(NodePtr p)
{
  int n = 0;

  // Prints from Head to Tail
  cout << setw(6) << left << setfill(' ') << "Index" << setw(10) << "Node" << '\n';
  while (p != NULL)
  {
    cout << setw(6) << n++ << p->num << '\n';
    p = p->next;
  }
}

// Method Overload
void LinkedList::print()
{
  this->print(this->head->next); // Set Head Node as p Node
}

// Print Nodes with a Recursive Method from Tail to Head
void LinkedList::printReverse(NodePtr p)
{
  static int n = this->length;

  // Prints from Tail to Head
  // NOTE: If the Print Statement is before the Recursive Function Call, Nodes will be Printed from Head to Tail

  if (p != NULL) // Same Expression as !p or p==0
  {
    this->printReverse(p->next);
    cout << setw(6) << n-- << p->num << '\n';

    return;
  }
  cout << setw(6) << left << setfill(' ') << "Index" << setw(10) << "Node" << '\n';
}

// Method Overload
void LinkedList::printReverse()
{
  this->printReverse(this->head->next); // Set Head Node as p Node
}

/*
// Count Nodes with a Recursive Method
int LinkedList::count(NodePtr p)
{
  if (p != NULL)
    return count(p->next) + 1;

  // Set Head Node as Current Node
  this->setHeadAsCurrent();

  return 0;
}
*/

// Method to Get Linked List Length
int LinkedList::getLength()
{
  return this->length;
}

// Method that Returns the Sum of All Node's Data Field
int LinkedList::total(NodePtr p)
{
  int sum = 0;

  while (p != NULL)
  {
    sum += p->num;
    p = p->next;
  }

  return sum;
}

// Method Overload
int LinkedList::total()
{
  return this->total(this->head->next); // Set Head Node as p Node
}

// Method that Returns the Highest Number in Linked List
int LinkedList::max(NodePtr p)
{
  static int m = INT_MIN;

  while (p != NULL)
  {
    // Node Number Value is Bigger
    if (p->num > m)
      m = p->num;

    p = p->next;
  }

  return m;
}

// Method Overload
int LinkedList::max()
{
  return this->max(this->head->next); // Set Head Node as p Node
}

/*
// Recursive Method that Returns the Highest Number in Linked List
int LinkedList::max()
{
  static int x = INT_MIN;
  NodePtr p = this->curr;

  if (p == NULL)
  {
    // Set Head Node as Current Node
    this->setHeadAsCurrent();

    return INT_MIN;
  }

  this->curr = this->curr->next;
  x = this->max();

  return x > p->num ? x : p->num;
}
*/

// Method that Checks if the Given Number is Inside Linked List
NodePtr LinkedList::linearSearch(NodePtr p, int key)
{
  NodePtr q;

  while (p != NULL)
  {
    if (key == p->num)
    {
      // Set p Node as Tail
      if (p->next == NULL)
        this->tail = q;

      // Move Node whose Key Matched Next to Head in Order to Improve Performance
      q->next = p->next;
      p->next = this->head->next;
      this->head->next = p;

      // Set Head Node as Current Node
      this->setHeadAsCurrent();
      return p;
    }
    q = p;
    p = p->next;
  }

  // Set Head Node as Current Node
  this->setHeadAsCurrent();
  return NULL;
}

// Method Overload
NodePtr LinkedList::linearSearch(int key)
{
  return this->linearSearch(this->head->next, key); // Set Head Node as p Node
}

/*
// Recursive Method that Checks if the Given Number is Inside Linked List
NodePtr LinkedList::linearSearch(int key)
{
  // Get Current Node
  NodePtr p = this->curr;

  if (p == NULL)
  {
    // Set Head Node as Current Node
    this->setHeadAsCurrent();
    return NULL;
  }

  if (key == p->num)
    return p;

  this->curr = this->curr->next;
  return this->linearSearch(key);
}
*/

// Function to Check if Key was Found
string isKey(NodePtr p)
{
  return p ? "Key Found" : "Key not Found";
}

// Method to Check if Node is not NULL
string isNull(NodePtr p)
{
  return p ? "Node is NULL" : "Node is not NULL";
}

int main()
{

  // Memory Allocation
  int numbers[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 25};

  // LinkedList list = LinkedList();
  // LinkedList list = LinkedList(1);
  LinkedList list = LinkedList(numbers, 11);

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
  list.remove();
  list.print();

  cout << "\nNodes (Reverse):\n";
  list.printReverse();

  // Max Number inside Linked List
  cout << "\nMax Number: " << list.max() << '\n';

  // Search for Number in Linked List
  NodePtr nodeFound;
  int key;

  key = 24;
  nodeFound = list.linearSearch(key);
  cout << "Search for Key '" << key << "': " << isKey(nodeFound) << '\n';

  key = 25;
  nodeFound = list.linearSearch(key);
  cout << "Search for Key '" << key << "': " << isKey(nodeFound) << '\n';

  key = 6;
  nodeFound = list.linearSearch(key);
  cout << "Search for Key '" << key << "': " << isKey(nodeFound) << '\n';

  // Print Nodes (Now, Node whose Key was Found is Next to Head)
  cout << "\nNodes after Linear Search:\n";
  list.print();

  // Insert Node
  list.insert(55);        // Next to Head
  list.insertAt(100, 6);  // At Index 6
  list.push_back(33);     // At Tail
  list.insertAt(77, -1);  // At Tail
  list.insertAt(400, -2); // Before Tail
  list.insertAt(898, 20); // At Tail
  list.insertAt(999, -1); // At Tail
  list.insert(13);        // Next to Head

  cout << "\nNodes after Insertion:\n";
  list.print();

  // Remove Node
  list.remove();     // Remove Node Next to Head
  list.removeAt(8);  // At Index 6
  list.removeAt(-4); // At Index -4
  list.pop();        // Remove Tail

  cout << "\nNodes after Deletion:\n";
  list.print();

  // Get Node
  int pos;

  pos = 13;
  cout << "\nGet Node at Index \'" << pos << "\': " << list.get(pos) << '\n';

  pos = 20;
  cout << "Get Node at Index \'" << pos << "\': " << list.get(pos) << '\n';

  pos = -5;
  cout << "Get Node at Index \'" << pos << "\': " << list.get(pos) << '\n';

  // Modify Node
  list.change(19, 4);

  cout << "\nNodes after Change:\n";
  list.print();
}