#include <cstdlib>
#include <iostream>
#include <string>
#include <limits.h>
#include <iomanip>

#include "base.h"

using std::cout;
using std::left;
using std::setfill;
using std::setw;
using std::string;

#ifndef CHARACTER_SINGLE_LINKED_LISTS
#define CHARACTER_SINGLE_LINKED_LISTS

// CHARACTER SINGLE LINKED LIST NAMESPACE
namespace characterSLL
{
  const int nIndex = 6;
  const int maxLen = 30;
}

// CHARACTER SINGLE LINKED LIST CLASS

class CharacterSingleLinkedList : public SingleLinkedList<string>
{
protected:
  // Protected Methods
  void print(SingleNodePtr<string>);
  void printReverse(SingleNodePtr<string>);

public:
  // Inherit Constructors
  using SingleLinkedList<string>::SingleLinkedList;

  // Constructors
  CharacterSingleLinkedList() : SingleLinkedList<string>(""){};

  // Public Methods
  void print() { return print(this->head->next); };               // Set Head Next Node as p Node
  void printReverse() { return printReverse(this->head->next); }; // ...

  void insertionSort(string);
  void removeLength(bool biggerThan, int n);
};

// Method to Insert Node by Insertion Sort
void CharacterSingleLinkedList::insertionSort(string data)
{
  SingleNodePtr<string> p, m, n;

  // Check Data length
  if (data.length() > characterSLL::maxLen)
    data = data.substr(0, characterSLL::maxLen - 1);

  // Get Lowercase Word
  for (int i = 0; i < data.length(); i++)
    data[i] = tolower(data[i]);

  // Insert Node Next to Head
  if (this->isEmpty())
  {
    this->push(data);
    return;
  }

  int pos = 0;
  n = this->head->next;
  p = this->head;

  while (n != NULL)
  {
    if (n->data.compare(data) >= 0)
    {
      // Insert Node at pos Index
      this->insertAt(data, pos);
      return;
    }

    p = n;
    n = n->next;
    pos++;
  }

  // Insert Node at Tail
  this->pushBack(data);
}

// Method to Remove Words with a Length Less than or Greater than n
void CharacterSingleLinkedList::removeLength(bool biggerThan, int n)
{
  SingleNodePtr<string> p, q;

  // Get Head Next Node
  p = this->head;

  int pos = 0;

  while (p->next != NULL)
  {
    // Move to Next Node
    q = p->next;

    // Check Length
    if (biggerThan && q->data.length() > n || !biggerThan && q->data.length() <= n)
    {
      // Remove Node
      if (pos == 0)
        this->remove();
      else if (pos == this->getLength() - 1)
        this->pop();
      else
        this->removeAt(pos);
    }
    else
    {
      // Move to Next Node
      p = p->next;

      // Increase pos
      pos++;
    }
  }
}

// Method Print Nodes from Head to Tail
void CharacterSingleLinkedList::print(SingleNodePtr<string> p)
{
  int n = 0;

  // Prints from Head to Tail
  cout << setw(characterSLL::nIndex) << left << setfill(' ') << "Index"
       << setw(characterSLL::maxLen + 1) << setfill(' ') << "Node"
       << "Length"
       << '\n';

  while (p != NULL)
  {
    cout << setw(characterSLL::nIndex) << setfill(' ') << n++
         << setw(characterSLL::maxLen + 1) << setfill(' ') << p->data
         << p->data.length()
         << '\n';

    p = p->next;
  }
}

// Print Nodes with a Recursive Method from Tail to Head
void CharacterSingleLinkedList::printReverse(SingleNodePtr<string> p)
{
  static int n = this->length - 1;

  // Prints from Tail to Head
  // NOTE: If the Print Statement is before the Recursive Function Call, Nodes will be Printed from Head to Tail
  if (p != NULL) // Same Expression as !p or p==0
  {
    this->printReverse(p->next);
    cout << setw(characterSLL::nIndex) << setfill(' ') << n--
         << setw(characterSLL::maxLen + 1) << setfill(' ') << p->data
         << p->data.length()
         << '\n';

    return;
  }

  // Prints Header
  cout << setw(characterSLL::nIndex) << left << setfill(' ') << "Index"
       << setw(characterSLL::maxLen + 1) << setfill(' ') << "Node"
       << "Length"
       << '\n';
}

#endif