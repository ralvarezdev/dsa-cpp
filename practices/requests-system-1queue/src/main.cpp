#include <string>
#include <iostream>
#include <filesystem>

#include "lib/terminal/cols.h"
#include "lib/terminal/input.h"
#include "lib/requests/requests.h"

using namespace std;

/*
NOTE: In this Practice, we're Challenged to Create a Requests System that's Sorted by Priority and by Order of Arrival,
with the Less Amount of Queues and Auxiliary Data Structures
*/

// --- Function Prototypes
void helpMessage();
void changeCwdToData();

int main(int argc, char **argv)
{
  // Desynchronize C++ Streams from C I/O Operations to Increase Performance
  std::ios::sync_with_stdio(false);

  // Change Path to 'src/data'
  changeCwdToData();

  // Students Header
  Col cols[5] = {
      Col("First Name", terminal::nFirstName),
      Col("Last Name", terminal::nLastName),
      Col("Title", terminal::nTitle),
      Col("Description", terminal::nDescription),
      Col("Priority", terminal::nPriority)};

  // Create Title Linked List
  ColLinkedList titleList(cols, 5, Col());

  // Create Requests Queue Linked List
  RequestQueueLinkedList requestsQueue = RequestQueueLinkedList();

  // Read requests.csv
  requestsQueue.readFile();

  // - Program Status Variables
  bool exit, confirmation;
  string inputWord;
  int id, pos, intCmd, timesExec = 0;
  requests::cmds cmd;

  while (!exit) // Main While Loop of the Program
  {
    // Check if Invoke Command Contains Program's Commands
    if (timesExec == 0 && argc > 1)
    { // Checks if it's a Command
      inputWord = argv[1];
      try
      {
        // Try to Get Command
        cmd = requests::cmds(stoi(inputWord));
      }
      catch (...)
      {
        // Throw Error Message
        pressEnterToCont("ERROR: Command not Found", true);
        break;
      }
    }
    else
    {
      // Print Help Message
      helpMessage();

      // Print New Line
      cout << '\n';

      // Get Command
      intCmd = getInteger("Enter Command", 1, cmds::cmdNull);
      cmd = cmds(intCmd);
    }

    // Increase Counter
    timesExec++;

    switch (cmd)
    {
    case requests::printAll:
      // Clear Terminal
      cout << clear;

      // Print Columns Header
      titleList.print();

      // Print Students
      requestsQueue.print();

      // Print New Line
      cout << '\n';

      pressEnterToCont("Press ENTER to Continue");
      break;

    case requests::addRequest:
      /*
            // Ask for Student ID
            id = getInteger("Enter Student ID to Remove", 1, requestsQueue.getLength());

            // Get Student Position in Linked List
            pos = requestsQueue.linearSearch(id);

            // Student not Found
            if (pos == -1)
            {
              pressEnterToCont("ERROR: Student not Found", true);
              break;
            }

            // Confirmation Message
            cout << "\n\n";
            if (booleanQuestion("Is this the Student you want to Remove?"))
            {
              requestsQueue.removeAt(pos);
              requestsQueue.overwriteCSV();
            }
      */
      break;

    case requests::help:
      break;

    case requests::exit:
      // Confirmation Message
      exit = booleanQuestion("Are you SURE to Exit");
      break;

    default:
      // Command not Found
      pressEnterToCont("ERROR: Command not Found", true);
      break;
    }
  }
}

// --- Functions

// Function to Print Help Message in the Terminal
void helpMessage()
{
  cout << clear;
  printTitle("WELCOME TO FLASH ACADEMIC REQUESTS SYSTEM");
  cout << "Database Manipulation Commands\n"
       << tab1 << addBrackets<int>(requests::printAll) << " Print Requests\n"
       << tab1 << addBrackets<int>(requests::addRequest) << " Add Request\n"
       << "Other Commands:\n"
       << tab1 << addBrackets<int>(requests::help) << " Help\n"
       << tab1 << addBrackets<int>(requests::exit) << " Exit\n";
}

// Function to Change Current Working Directory to 'src/data'
void changeCwdToData()
{
  try
  {
    filesystem::path mainCppPath = __FILE__;              // Path to main.cpp File
    filesystem::path srcPath = mainCppPath.parent_path(); // Path to 'src' Folder

    filesystem::path dataDir = "data";
    filesystem::path dataPath = srcPath / dataDir; // Concatenate srcPath with DataDir to get the FUll Path to the .csv Files

    filesystem::current_path(dataPath); // Change cwd to '.../src/data'
  }
  catch (...)
  {
    pressEnterToCont("Error: main.cpp File is not Inside 'src' Folder", true);
  }
}