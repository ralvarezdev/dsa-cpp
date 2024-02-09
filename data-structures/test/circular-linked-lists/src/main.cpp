#include <string>
#include <iostream>

#include "../../../circular-linked-lists/number.h"

using namespace std;

// Function to Check if Key was Found
template <typename T>
string isKey(DoublyNodePtr<T> p)
{
  return p ? "Key Found" : "Key not Found";
}

// Method to Check if Node is not NULL
template <typename T>
string isNull(DoublyNodePtr<T> p)
{
  return p ? "Node is NULL" : "Node is not NULL";
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
  double numbers[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 25};

  NumberCircularLinkedList<double> list(numbers, 11, -1);

  // Check if it's Empty
  string isEmpty = list.isEmpty() ? "True" : "False";
  cout << "Is Empty? " << isEmpty << "\n\n";

  // Check List Length
  int length = list.getLength();
  cout << "List Length: " << length << "\n\n";

  // Get Total
  double total = list.total();
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
  DoublyNodePtr<double> nodeFound;
  double key;

  key = 24;
  nodeFound = list.linearSearch(key);
  cout << "Search for Key '" << key << "': " << isKey<double>(nodeFound) << '\n';

  key = 25;
  nodeFound = list.linearSearch(key);
  cout << "Search for Key '" << key << "': " << isKey<double>(nodeFound) << '\n';

  key = 6;
  nodeFound = list.linearSearch(key);
  cout << "Search for Key '" << key << "': " << isKey<double>(nodeFound) << '\n';

  // Insert Node
  list.push(55);          // Next to Head
  list.insertAt(100, 6);  // At Index 6
  list.pushBack(33);      // At Tail
  list.insertAt(77, -1);  // At Tail
  list.insertAt(400, -2); // Before Tail
  list.insertAt(898, 20); // At Tail
  list.insertAt(999, -1); // At Tail
  list.push(13);          // Next to Head

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

  // Compare Nodes
  int pos1 = 5, pos2 = 9;

  cout << "\nCompare Node at Index \'" << pos1
       << "\' with Node at Index \'" << pos2 << "\': "
       << checkCompare(list.compare(pos1, pos2)) << '\n';
}