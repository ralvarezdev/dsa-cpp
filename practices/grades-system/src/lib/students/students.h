#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "../namespaces.h"
#include "../terminal/input.h"
#include "../../../../../data-structures/linked-lists/base.h"

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
using namespace students;

#ifndef STUDENTS_LINKED_LISTS
#define STUDENTS_LINKED_LISTS

// STUDENT CLASS

class Student
{
public:
  int id = -1;
  string firstName = "";
  string lastName = "";
  string email = "";
  students::genders gender = genderNull;
  int grades[nCourses] = {-1};
  float prom = -1;

  // Constructors
  Student();
  Student(int, string, string, string, string, int *);

  // Public Methods
  void getGender(string);
  // void createFile();
};

// STUDENT LINKED LIST CLASS

class StudentLinkedList : public LinkedList<Student>
{
public:
  // Inherit Constructors
  using LinkedList<Student>::LinkedList;

  // Public Methods
  void print();
  void readFile();
};

// STUDENT CLASS

// Student Class Constructors
Student::Student()
{
  return;
}

Student::Student(int id, string firstName, string lastName, string email, string gender, int *grades)
{
  // Assign Data
  this->id = id;
  this->firstName = firstName;
  this->lastName = lastName;
  this->email = email;

  // Assign Gender
  this->getGender(gender);

  // Assign Grades
  float sum;
  for (int i = 0; i < nCourses; i++)
  {
    this->grades[i] = grades[i];
    sum += grades[i];
  }

  this->prom = sum / nCourses;
}

// Method to Get Gender
void Student::getGender(string gender)
{
  string genderLower = getLower(gender);

  // Check Gender
  if (genderLower == "female")
    this->gender = genders::female;
  else if (genderLower == "male")
    this->gender = genders::male;
  else
    this->gender = genders::nonBinary;
};

// void createFile();

// STUDENT LINKED LIST CLASS

// Method to Print Students
void StudentLinkedList::print()
{
  // Read students.csv
  if (this->length == 0)
    this->readFile();

  NodePtr<Student> p = this->head->next;
  ostringstream message;

  Student student;

  message << left;

  // Prints from Head to Tail
  while (p != NULL)
  {
    student = p->data;

    // Add Student Data
    message << setw(nId) << setfill(' ') << student.id
            << setw(nFirstName) << setfill(' ') << student.firstName
            << setw(nLastName) << setfill(' ') << student.lastName;

    // Add Gender
    if (student.gender == genders::female)
      message
          << setw(nGender) << setfill(' ') << "Female";
    else if (student.gender == genders::male)
      message
          << setw(nGender) << setfill(' ') << "Male";
    else
      message << setw(nGender) << setfill(' ') << "Other";

    // Add Course Grades
    message << setw(nProm) << setfill(' ') << student.prom;
    for (int i = 0; i < nCourses; i++)
      message << setw(nCourse) << setfill(' ') << student.grades[i];

    // Add New Line
    message << '\n';

    p = p->next;
  }

  cout << message.str();
}

// Method to Read students.csv File
void StudentLinkedList::readFile()
{
  string firstName, lastName, email, gender;
  int id, grades[nCourses];

  string line, word;
  int count, i;

  ifstream studentCSV(students::studentFilename);

  if (!studentCSV.is_open()) // Couldn't Access to studentCSV
  {
    studentCSV.close();
    pressEnterToCont("Error: File Not Found. Press ENTER to go Back to Main Menu", true);
    return; // End this Function
  }

  // Remove Header
  getline(studentCSV, line);

  while (getline(studentCSV, line)) // Get Students
    try
    {
      if (line.length() == 0)
        continue;

      fill(grades, grades + nCourses, 0);

      stringstream file(line);

      i = count = 0;
      while (getline(file, word, sep))
      {
        if (word.length() != 0)
          switch (count)
          {
          case 0:
            id = stoi(word);
            break;
          case 1:
            firstName = word;
            break;
          case 2:
            lastName = word;
            break;
          case 3:
            email = word;
            break;
          case 4:
            gender = word;
            break;

          default:
            grades[i++] = stoi(word);
            break;
          }

        count++;
      }

      // Save Grades
      Student *newStudent = new Student(id, firstName, lastName, email, gender, grades);

      this->push_back(*newStudent);
    }
    catch (...)
    {
      // It will Ignore the Line that was Read from movies.csv
    }

  studentCSV.close();
}

#endif