#include <string>
#include <iostream>

#include "../../../doubly-linked-lists/number.h"
#include "../../../single-linked-lists/number.h"

using namespace std;

// Function to Check if Key was Found
string isKey(bool p)
{
  return p ? "Key Found" : "Key not Found";
}

// Function to Check compare Return Value
string checkCompare(int r)
{
  if (r == 0)
    return "Equal";
  else if (r == 1)
    return "First Node is Greater than Second Node";
  else if (r == 2)
    return "Second Node is Greater than First Node";

  return "There's Some Node that's Null";
}

int main()
{
  // Memory Allocation
  double numbers[14] = {10, 1, 2, 3, 9, 4, 5, 4, 6, 7, 8, 9, 10, 25};

  NumberDoublyLinkedList<double> *list = new NumberDoublyLinkedList<double>(numbers, 14, -1);

  // Check if it's Empty
  string isEmpty = list->isEmpty() ? "True" : "False";
  cout << "Is Empty? " << isEmpty << "\n\n";

  // Check List Length
  int length = list->getLength();
  cout << "List Length: " << length << "\n\n";

  // Get Total
  double total = list->total();
  cout << "List Total: " << total << "\n\n";
  // Print Nodes
  cout << "Nodes:\n";
  list->print();

  cout << "\nFirst Node Removed:\n";
  list->remove();
  list->print();

  cout << "\nNodes (Reverse):\n";
  list->printReverse();

  // Max Number inside Linked List
  cout << "\nMax Number: " << list->max() << '\n';

  // Search for Number in Linked List
  bool nodeFound;
  double key;

  key = 24;
  nodeFound = list->linearSearch(key);
  cout << "Search for Key '" << key << "': " << isKey(nodeFound) << '\n';

  key = 25;
  nodeFound = list->linearSearch(key);
  cout << "Search for Key '" << key << "': " << isKey(nodeFound) << '\n';

  key = 6;
  nodeFound = list->linearSearch(key);
  cout << "Search for Key '" << key << "': " << isKey(nodeFound) << '\n';

  // Insert Node
  list->push(55);           // At Head
  list->insertAt(88, 3);    // At Index 3
  list->insertAt(100, 6);   // At Index 6
  list->insertAt(200, 11);  // At Index 11
  list->pushBack(33);       // At Tail
  list->insertAt(77, -1);   // At Tail
  list->insertAt(300, -15); // At Index -15
  list->insertAt(400, -2);  // Before Tail
  list->insertAt(898, 30);  // Should not be Inserted
  list->insertAt(999, -1);  // At Tail
  list->push(13);           // At Head

  cout << "\nNodes after Insertion:\n";
  list->print();

  // Remove Node
  list->remove();     // Remove Head
  list->removeAt(8);  // At Index 8
  list->removeAt(-4); // At Index -4
  list->pop();        // Remove Tail

  cout << "\nNodes after Deletion:\n";
  list->print();

  // Get Node
  int pos;

  pos = 7;
  cout << "\nGet Node at Index \'" << pos << "\': " << list->get(pos) << '\n';

  pos = 13;
  cout << "Get Node at Index \'" << pos << "\': " << list->get(pos) << '\n';

  pos = 20;
  cout << "Get Node at Index \'" << pos << "\': " << list->get(pos) << '\n';

  pos = -5;
  cout << "Get Node at Index \'" << pos << "\': " << list->get(pos) << '\n';

  pos = -12;
  cout << "Get Node at Index \'" << pos << "\': " << list->get(pos) << '\n';

  // Modify Node
  list->change(19, 4);

  cout << "\nNodes after Change:\n";
  list->print();

  // Compare Nodes
  int pos1 = 5, pos2 = 9;

  cout << "\nCompare Node at Index \'" << pos1
       << "\' with Node at Index \'" << pos2 << "\': "
       << checkCompare(list->compare(pos1, pos2)) << '\n';

  // Create Copy Single Linked List
  NumberSingleLinkedList<double> *listCopy = list->SingleLinkedList();

  cout << "\nSingle List:\n";
  listCopy->print();

  // Deallocate Memory
  delete list, listCopy;
}