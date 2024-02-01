#include <string>
#include <iostream>
#include <filesystem>

#include "../../../data-structures/linked-lists/base.h"
#include "lib/terminal/input.h"

using namespace std;

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