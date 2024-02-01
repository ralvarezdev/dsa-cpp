#include <string>
#include <iostream>
#include <filesystem>

#include "lib/terminal/cols.h"
#include "lib/terminal/input.h"

using namespace std;

int main()
{
  // Students Header
  Col cols[10] = {
      Col("Id", terminal::id),
      Col("First Name", terminal::firstName),
      Col("Last Name", terminal::lastName),
      Col("Email", terminal::email),
      Col("Gender", terminal::gender),
      Col("OOP", terminal::course),
      Col("DSA", terminal::course),
      Col("DB", terminal::course),
      Col("Math", terminal::course),
      Col("Stats", terminal::course)};

  ColLinkedList title(cols, 10, Col("", 0));

  title.print();
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