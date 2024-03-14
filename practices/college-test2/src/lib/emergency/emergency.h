#include <iostream>
#include <fstream>
#include <sstream>

#include "../../../../../data-structures/queue/base.h"

using namespace std;

#ifndef EMERGENCY_QUEUE
#define EMERGENCY_QUEUE

class Emergency
{
public:
  int type;
  int person;

  // Constructors
  Emergency(){};
  Emergency(int, int);
};

// Emergency Constructors
Emergency::Emergency(int type, int person)
{
  this->type = type;
  this->person = person;
}

// EMERGENCY QUEUE LINKED LIST CLASS
// FIFO
// First-in, First-out

class EmergencyQueue : public QueueLinkedList<Emergency>
{
public:
  // Inherit Constructors
  using QueueLinkedList<Emergency>::QueueLinkedList;

  // Public Methods
  void push(Emergency); // Method that Overwrites the push Method Inherited by its Base Class
  void readFile();
  void print();
};

// Method to Push Emergencies
void EmergencyQueue::push(Emergency e)
{
  Emergency t;
  int iter = 0;

  // First Emergency
  Emergency first = this->first();

  // Compare Emergency to Push with the First One
  while (first.person <= e.person && first.type <= e.type)
  {
    // Pop First Emergency and Push it Back
    t = this->pop();
    this->push(t);

    first = this->first();

    iter++;
  }

  // Push Emergency to Queue
  this->enqueue(e);

  // Get Queue Length
  int length = this->getLength();

  // Push Left Emergencies at the Original Order with the One that was Inserted
  for (int i = 0; i < length - iter + 1; i++)
  {
    // Pop First Emergency and Push it Back
    t = this->pop();
    this->push(t);
  }
}

// Method to Insert Emergencies while Reading unknown.txt while
void EmergencyQueue::readFile()
{
  string line, word;
  int type, person;

  ifstream emergencies("unknown.txt");

  if (!emergencies.is_open())
  {
    cout << "File couldn't be Opened";
    return;
  }

  while (getline(emergencies, line))
  {
    stringstream file(line);

    try
    {
      // Get Emergency Type
      getline(file, word, ' ');
      type = stoi(word);

      while (getline(file, word, ' '))
      {
        // Get Person
        person = stoi(word);

        // Pushed Emergency to Queue
        this->push(Emergency(type, person));
      }
    }
    catch (...)
    {
      // Ignore
    }
  }
}

// Method to Print Emergencies from Queue
void EmergencyQueue::print()
{
  Emergency e;
  int iter = 0;

  ostringstream output;

  output << "Emergencies:\n";

  while (iter != this->getLength())
  {
    // Get First Emergency
    e = this->dequeue();

    // Add Emergency to output
    output << '[' << e.type << "] ";

    switch (e.person)
    {
    case 'f':
      output << 'Girl';
      break;
    case 'm':
      output << "Boy";
      break;
    case 'F':
      output << "Woman";
      break;
    case 'M':
      output << "Man";
      break;
    }

    // Push Back Emergency
    this->push(e);

    output << '\n';

    iter++;
  }

  cout << output.str();
}

#endif