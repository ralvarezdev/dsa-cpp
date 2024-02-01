#include <string>
#include <iomanip>

#include "../namespaces.h"
#include "../terminal/input.h"
#include "../../../../../data-structures/linked-lists/base.h"

using std::string;
using namespace students;

#ifndef STUDENTS_LINKED_LISTS
#define STUDENTS_LINKED_LISTS

// STUDENT CLASS

class Student
{
public:
  string firstName;
  string lastName;
  string email;
  students::genders gender;
  int *grades;
  float prom;

  // Constructors
  Student();
  Student(string, string, string, students::genders, int *, float);

  // Public Methods
  // void createFile();
};

// STUDENT LINKED LIST CLASS

class StudentLinkedList : public LinkedList<Student>
{
public:
  // Public Methods
  void print();
};

// STUDENT CLASS

// Student Class Constructors
Student::Student()
{
  return;
}

Student::Student(string firstName, string lastName, string email, students::genders gender, int *grades, float prom)
{
  this->firstName = firstName;
  this->lastName = lastName;
  this->email = email;
  this->gender = gender;
  this->grades = grades;
  this->prom = prom;
}

// void createFile();

// STUDENT LINKED LIST CLASS

// Method to Print Students
/*
void StudentLinkedList::print()
{
  NodePtr<Col> p = this->head->next;
  ostringstream message;

  int width;
  string name;

  message << left;

  // Prints from Head to Tail
  while (p != NULL)
  {
    width = p->data.getWidth();
    name = p->data.getName();

    message << setw(width) << setfill(' ') << name;
    p = p->next;
  }

  // Print Title
  printTitle(message.str());
}
 */

#endif