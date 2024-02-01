#include <string>
#include <iostream>
#include <filesystem>

#include "lib/terminal/cols.h"
#include "lib/terminal/input.h"
#include "lib/students/students.h"

using namespace std;

// --- Function Prototypes
void changeCwdToData();

int main()
{
  // Desynchronize C++ Streams from C I/O Operations to Increase Performance
  std::ios::sync_with_stdio(false);

  // Change Path to 'src/data'
  changeCwdToData();

  // Students Header
  Col cols[11] = {
      Col("Id", terminal::nId),
      Col("First Name", terminal::nFirstName),
      Col("Last Name", terminal::nLastName),
      Col("Gender", terminal::nGender),
      Col("Prom", terminal::nProm),
      Col("OOP", terminal::nCourse),
      Col("DSA", terminal::nCourse),
      Col("DB", terminal::nCourse),
      Col("Math", terminal::nCourse),
      Col("Stats", terminal::nCourse)};

  // Create Title Linked List
  ColLinkedList titleList(cols, 11, Col());

  StudentLinkedList studentList = StudentLinkedList(Student());

  titleList.print();
  studentList.print();
}

// --- Functions

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