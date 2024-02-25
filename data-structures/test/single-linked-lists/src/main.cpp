#include <string>
#include <iostream>

#include "../../../single-linked-lists/number.h"

using namespace std;

// Function to Check if Key was Found
string isKey(bool p)
{
  return p ? "Key Found" : "Key not Found";
}

int main()
{
  // Memory Allocation
  double numbers[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 25};

  // NumberLinkedList list = NumberLinkedList();
  // NumberLinkedList list = NumberLinkedList(1);
  NumberSingleLinkedList<double> *list = new NumberSingleLinkedList<double>(numbers, 11, -1);

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

  // Print Nodes (Now, Node whose Key was Found is Next to Head)
  cout << "\nNodes after Linear Search:\n";
  list->print();

  // Insert Node
  list->push(55);          // Next to Head
  list->insertAt(100, 6);  // At Index 6
  list->pushBack(33);      // At Tail
  list->insertAt(77, -1);  // At Tail
  list->insertAt(400, -2); // Before Tail
  list->insertAt(898, 20); // Should not be Inserted
  list->insertAt(999, -1); // At Tail
  list->push(13);          // Next to Head

  cout << "\nNodes after Insertion:\n";
  list->print();

  // Remove Node
  list->remove();     // Remove Node Next to Head
  list->removeAt(8);  // At Index 8
  list->removeAt(-4); // At Index -4
  list->pop();        // Remove Tail

  cout << "\nNodes after Deletion:\n";
  list->print();

  // Get Node
  int pos;

  pos = 7;
  cout << "\nGet Node at Index \'" << pos << "\': " << list->get(pos) << '\n';

  pos = 12;
  cout << "Get Node at Index \'" << pos << "\': " << list->get(pos) << '\n';

  pos = 20;
  cout << "Get Node at Index \'" << pos << "\': " << list->get(pos) << '\n';

  pos = -5;
  cout << "Get Node at Index \'" << pos << "\': " << list->get(pos) << '\n';

  // Modify Node
  list->change(19, 4);

  cout << "\nNodes after Change:\n";
  list->print();

  // Deallocate Memory
  delete list;
}