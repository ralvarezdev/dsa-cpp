#include <string>
#include <iostream>

#include "../../data-structures/linked-lists.h"

using std::cin;
using std::cout;
using std::string;

// Function to Check if Key was Found
template <typename T>
string isKey(NodePtr<T> p)
{
  return p ? "Key Found" : "Key not Found";
}

// Method to Check if Node is not NULL
template <typename T>
string isNull(NodePtr<T> p)
{
  return p ? "Node is NULL" : "Node is not NULL";
}

int main()
{
  // Memory Allocation
  int numbers[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 25};

  // LinkedList list = LinkedList();
  // LinkedList list = LinkedList(1);
  LinkedList<int> list(numbers, 11);

  // Check if it's Empty
  string isEmpty = list.isEmpty() ? "True" : "False";
  cout << "Is Empty? " << isEmpty << "\n\n";

  // Check List Length
  int length = list.getLength();
  cout << "List Length: " << length << "\n\n";

  /*
    // Get Total
    int total = list.total();
    cout << "List Total: " << total << "\n\n";
  */

  // Print Nodes
  cout << "Nodes:\n";
  list.print();

  cout << "\nFirst Node Removed:\n";
  list.remove();
  list.print();

  cout << "\nNodes (Reverse):\n";
  list.printReverse();

  /*
    // Max Number inside Linked List
    cout << "\nMax Number: " << list.max() << '\n';
  */

  // Search for Number in Linked List
  NodePtr<int> nodeFound;
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