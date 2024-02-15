#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>

#include "lib/terminal/input.h"
#include "../../../queue/base.h"

using namespace std;

// --- Function Prototypes
void changeCwdToData();

int main()
{
  // Create Queue
  QueueLinkedList<int> *queue = new QueueLinkedList<int>(-1);

  // Move to 'src/data'
  changeCwdToData();

  // Read from numbers.txt
  string line;

  ifstream numbersTXT("numbers.txt");

  if (!numbersTXT.is_open()) // Couldn't Access to numbersTXT
  {
    numbersTXT.close();
    pressEnterToCont("Error: File Not Found. Press ENTER to go Back to Main Menu", true);
    return -1; // End Program
  }

  while (getline(numbersTXT, line)) // Get Numbers
    try
    {
      if (line.length() == 0)
        continue;

      /*
            // Testing
            cout << line << ' ' << queue->getLength() << '\n';
      */

      queue->push(stoi(line));
    }
    catch (...)
    {
      // It will Ignore the Line that was Read from numbers.txt
    }

  numbersTXT.close();

  // Print Numbers Read
  cout << "Queue Nodes:\n";
  while (queue->getLength() > 0)
    cout << queue->pop() << '\n';
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
