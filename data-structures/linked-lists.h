#include <cstdlib>

#ifndef LINKED_LISTS
#define LINKED_LISTS

// NODE CLASS
// Self-Referential Structure

template <class T>
class Node
{
public:
  T data;
  Node *next = NULL;

  // Constructor
  Node();
  Node(T);
  Node(T, Node *);
};

// NodePtr Definition
template <class T>
using NodePtr = Node<T> *;

// LINKED LIST CLASS

template <class T>
class LinkedList
{
private:
  NodePtr<T> head;
  NodePtr<T> tail;
  NodePtr<T> curr;

  int length = 0;

  // Private Methods
  void increaseLength();
  void increaseLength(int);
  void decreaseLength();
  NodePtr<T> move(NodePtr<T>, int);

public:
  // Constructors
  LinkedList();
  LinkedList(T);
  LinkedList(T[], int);
  ~LinkedList();

  // Public Methods
  bool isEmpty();
  void insert(T);
  void push_back(T);
  void insertAt(T, int);
  T remove();
  T pop();
  T removeAt(int);
  T change(T, int);
  T get(int);
  void setCurrent(NodePtr<T>);
  void setCurrent();
  void print();
  void print(NodePtr<T>);
  void printReverse();
  void printReverse(NodePtr<T>);
  // int count(NodePtr<T>);
  int getLength();
  // int total();
  // int total(NodePtr<T>);
  // int max();
  // int max(NodePtr<T>);
  NodePtr<T> linearSearch(T);
  NodePtr<T> linearSearch(NodePtr<T>, T);
};

// Explicit Template Initialization
template class Node<int>;
template class LinkedList<int>;

#endif