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
private:
  int id = -1;
  string firstName = "";
  string lastName = "";
  string email = "";
  students::genders gender = genderNull;
  int grades[nCourses] = {-1};
  float prom = -1;

public:
  // Constructors
  Student();
  Student(int, string, string, string, string, int *);

  // Public Methods
  int getId();
  string getFirstName();
  string getLastName();
  string getEmail();
  students::genders getGender();
  int getGrade(int);
  float getProm();
  void setGender(string);
  // void createFile();
};

// STUDENT LINKED LIST CLASS

class StudentLinkedList : public LinkedList<Student>
{
public:
  // Inherit Constructors
  using LinkedList<Student>::LinkedList;

  // Public Methods
  void insertionSort(Student);
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
  this->setGender(gender);

  // Assign Grades
  float sum;
  for (int i = 0; i < nCourses; i++)
  {
    this->grades[i] = grades[i];
    sum += grades[i];
  }

  this->prom = sum / nCourses;
}

// Getters

// Method to Get ID
int Student::getId()
{
  return this->id;
}

// Method to Get First name
string Student::getFirstName()
{
  return this->firstName;
}

// Method to Get Last Name
string Student::getLastName()
{
  return this->lastName;
}

// Method to Get Email
string Student::getEmail()
{
  return this->email;
}

// Method to Get Gender
students::genders Student::getGender()
{
  return this->gender;
}

// Method to Get Grade at Given Index
int Student::getGrade(int index)
{
  return this->grades[index];
}

// Method to Get Prom
float Student::getProm()
{
  return this->prom;
}

// Method to Set Gender
void Student::setGender(string gender)
{
  string genderLower = getLower(gender);

  // Check Gender
  if (genderLower == "female")
    this->gender = genders::female;
  if (genderLower == "male")
    this->gender = genders::male;
  else
    this->gender = genders::nonBinary;
};

// void createFile();

// STUDENT LINKED LIST CLASS

// Method to Insert in a Sorted Student Linked List
void StudentLinkedList::insertionSort(Student student)
{
  NodePtr<Student> p, q, n;
  float pProm, studentProm;
  int compareFirstName, compareLastName;

  p = this->head;
  q = NULL;

  while (true)
  {
    q = p;
    p = p->next;

    // Reached Tail Node
    if (p == NULL)
      break;

    pProm = p->data.getProm();
    studentProm = student.getProm();

    // pProm is Less
    if (pProm < studentProm)
      break;
    // pProm is Equal is Equal to studentProm
    else if (pProm == studentProm)
    {
      compareFirstName = student.getLastName().compare(p->data.getLastName()) < 0;

      // Student whose Last Name is being Compared Must Go First
      if (compareFirstName < 0)
        break;
      // Student whose First Name is being Compared Must Go First
      else if (compareFirstName > 0)
      {
        compareLastName = student.getLastName().compare(p->data.getLastName());

        if (compareLastName < 0)
          break;
      }
    }
  }

  // Create new Node, and Insert between q and p Node
  n = new Node(student);
  q->next = n;
  n->next = p;
}

// Method to Print Students
void StudentLinkedList::print()
{
  // Read students.csv
  if (this->length == 0)
    this->readFile();

  NodePtr<Student> p = this->head->next;
  ostringstream message;

  Student student;
  students::genders gender;

  message << left;

  // Prints from Head to Tail
  while (p != NULL)
  {
    student = p->data;

    // Add Student Data
    message << setw(nId) << setfill(' ') << student.getId()
            << setw(nFirstName) << setfill(' ') << student.getFirstName()
            << setw(nLastName) << setfill(' ') << student.getLastName();

    // Add Gender
    gender = student.getGender();
    if (student.getGender() == genders::female)
      message << setw(nGender) << setfill(' ') << "Female";
    else if (student.getGender() == genders::male)
      message << setw(nGender) << setfill(' ') << "Male";
    else
      message << setw(nGender) << setfill(' ') << "Other";

    // Add Course Grades
    message << setw(nProm) << setfill(' ') << student.getProm();
    for (int i = 0; i < nCourses; i++)
      message << setw(nCourse) << setfill(' ') << student.getGrade(i);

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

      this->insertionSort(*newStudent);
    }
    catch (...)
    {
      // It will Ignore the Line that was Read from movies.csv
    }

  studentCSV.close();
}

#endif