#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <limits.h>
#include <iomanip>
#include <fstream>

#include "../../../../../data-structures/queue/base.h"
#include "../terminal/input.h"
#include "../terminal/ansiEsc.h"
#include "../namespaces.h"

using namespace std;

using std::cout;
using std::fill;
using std::ifstream;
using std::left;
using std::ostringstream;
using std::setfill;
using std::setw;
using std::string;
using std::stringstream;

using namespace files;
using namespace terminal;
using namespace requests;

#ifndef REQUEST_QUEUE_LINKED_LIST
#define REQUEST_QUEUE_LINKED_LIST

// REQUEST CLASS

class Request
{
private:
  string firstName = "";
  string lastName = "";
  string title = "";
  string description = "";
  requests::priority priority = requests::priorityNull;

public:
  // Constructors
  Request();
  Request(string, string, string, string, requests::priority);

  // Public Methods
  string getFirstName();
  string getLastName();
  string getTitle();
  string getDescription();
  requests::priority getPriority();
};

// REQUEST QUEUE LINKED LIST CLASS

class RequestQueueLinkedList : public QueueLinkedList<Request>
{
private:
  QueueLinkedList<Request> *auxQueue = new QueueLinkedList<Request>(Request());

public:
  // Inherit Constructors
  using QueueLinkedList<Request>::QueueLinkedList;

  // Public Methods
  requests::priority moveToAuxQueue();
  void moveFromAuxQueue();
  void insertByPriority(Request);
  void readFile();
  void overwriteCSV();
};

// REQUESTS CLASS

// Request Class Constructors
Request::Request()
{
  return;
}

Request::Request(string firstName, string lastName, string title, string description, requests::priority priority)
{
  // Assign Data
  this->firstName = firstName;
  this->lastName = lastName;
  this->title = title;
  this->description = description;
  this->priority = priority;
}

// Getters

// Method to Get First Name
string Request::getFirstName()
{
  return this->firstName;
}

// Method to Get Last Name
string Request::getLastName()
{
  return this->lastName;
}

// Method to Get Description
string Request::getDescription()
{
  return this->description;
}

// Method to Get Title
string Request::getTitle()
{
  return this->title;
}

// Method to Get Priority
requests::priority Request::getPriority()
{
  return this->priority;
}

// REQUEST QUEUE LINKED LIST CLASS

// Method to Pop Node from RequestQueueLinkedList and Push it to auxQueue
requests::priority RequestQueueLinkedList::moveToAuxQueue()
{
  // Temp Request
  Request temp;

  // Pop First Request from RequestQueueLinkedList
  temp = this->pop();

  // Push First Request to auxQueue
  this->auxQueue->push(temp);

  return temp.getPriority();
}

// Method to Pop Node from auxQueue and Push it to RequestQueueLinkedList
void RequestQueueLinkedList::moveFromAuxQueue()
{
  // Temp Request
  Request temp;

  // Pop First Request from auxQueue
  temp = this->auxQueue->pop();

  // Push First Request to RequestQueueLinkedList
  this->push(temp);
}

// Method to Push Node by Priority
void RequestQueueLinkedList::insertByPriority(Request request)
{
  // Insert at the End
  if (requests::priority::students)
  {
    this->push(request);
    return;
  }

  // Temp Priority
  requests::priority tempPriority;

  // Move Nodes to auxQueue, until New Request can be Pushed at the Right Order and Priority Position
  while (tempPriority != request.getPriority() + 1)
    // Move Node from RequestQueueLinkedList to auxQueue
    tempPriority = this->moveToAuxQueue();

  // Push New Request to auxQueue
  this->auxQueue->push(request);

  // Move Nodes Left from RequestQueueLinkedList to auxQueue
  while (!this->isEmpty())
    // Move Node from RequestQueueLinkedList to auxQueue
    this->moveToAuxQueue();

  // Move Nodes Back from auxQueue to RequestQueueLinkedList
  while (!this->auxQueue->isEmpty())
    // Move Node from auxQueue to RequestQueueLinkedList
    this->moveFromAuxQueue();
}

// Method to Read requests.csv File
void RequestQueueLinkedList::readFile()
{
  string firstName, lastName, title, description;
  requests::priority priority;

  string line, word;
  int count;

  ifstream requestsCSV(requests::requestsFilename);

  if (!requestsCSV.is_open()) // Couldn't Access to requestsCSV
  {
    requestsCSV.close();
    pressEnterToCont("Error: File Not Found. Press ENTER to go Back to Main Menu", true);
    return; // End this Function
  }

  // Remove Header
  getline(requestsCSV, line);

  while (getline(requestsCSV, line)) // Get Requests
    try
    {
      if (line.length() == 0)
        continue;

      stringstream file(line);

      count = 0;
      while (getline(file, word, sep))
      {
        if (word.length() != 0)
          switch (count)
          {
          case 0:
            firstName = word;
            break;
          case 1:
            lastName = word;
            break;
          case 2:
            title = word;
            break;
          case 3:
            description = word;
            break;
          case 4:
            priority = requests::priority(stoi(word));
            break;

          default:
            break;
          }

        count++;
      }

      // Save Request
      Request *newRequest = new Request(firstName, lastName, title, description, priority);

      // Insert Request
      this->insertByPriority(*newRequest);

      // Increment Counter
      this->increaseLength();
    }
    catch (...)
    {
      // It will Ignore the Line that was Read from movies.csv
    }

  requestsCSV.close();
}

// Method to Overwite requests.csv
void RequestQueueLinkedList::overwriteCSV()
{
  SingleNodePtr<Request> p;
  Request request;

  ostringstream content;
  ofstream requestsCSV(requests::requestsFilename);

  content << "first_name,last_name,title,description,priority\n"; // Overwrite Header

  // Move Nodes Left from RequestQueueLinkedList to auxQueue
  while (!this->isEmpty())
  {
    // Pop First Request from RequestQueueLinkedList
    request = this->pop();

    // Add Request Data
    content << request.getFirstName() << sep
            << request.getLastName() << sep
            << request.getTitle()
            << request.getDescription() << sep
            << request.getPriority() << sep
            << '\n';

    // Push First Request to auxQueue
    this->auxQueue->push(request);
  }

  // Move Nodes Back to RequestQueueLinkedList
  while (!this->auxQueue->isEmpty())
    // Move Node from RequestQueueLinkedList to auxQueue
    moveFromAuxQueue();

  requestsCSV << content.str(); // Write Content to requests.csv
  requestsCSV.close();
}

#endif