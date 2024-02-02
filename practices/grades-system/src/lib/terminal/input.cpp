#include <string>
#include <iostream>
#include <sstream>

#include "ansiEsc.h"

using std::cin;
using std::cout;
using std::getline;
using std::ostringstream;
using std::string;

// --- Function Prototypes
void pressEnterToCont(string message, bool warning);
string getLower(string word);
bool booleanQuestion(string message);
int getInteger(string message, int low, int high);

// --- Functions

// Boolean Question
bool booleanQuestion(string message)
{
  string input;
  char c;

  while (true)
  {
    cout << "- " << message << " [y/N] ";
    getline(cin, input);

    c = tolower(input[0]);
    cout << c;

    if (c == 'y')
    {
      cout << '\n';
      return true;
    }
    else if (c == 'n')
    {
      cout << '\n';
      return false;
    }

    // Print Error Message
    pressEnterToCont("ERROR: It's a Yes/No Question. You must type 'y', 'Y' or 'n', 'N'", true);
  }
}

// Function to Ask for a Integer Input
int getInteger(string message, int low, int high)
{
  string temp;
  int amount;

  while (true)
    try // Get Integer
    {
      cout << message << ": ";
      getline(cin, temp);
      amount = stoi(temp);

      if (amount >= low && amount <= high)
        return amount;
      else
        // Number Out of Range
        throw(-1);
    }
    catch (...)
    {
      ostringstream stream;

      stream << "The Number is Out of that Range"
             << " [" << low << '-' << high << "]";

      pressEnterToCont(stream.str(), true);
    }
}

// Function to Stop the Program Flow while the User doesn't press the ENTER key
void pressEnterToCont(string message, bool warning = false)
{
  string _;

  printTitle(message, warning);
  getline(cin, _);
}

// Function to Get a Lowercase String
string getLower(string word)
{
  string wordToLower;

  for (int i = 0; i < word.length(); i++)
    wordToLower += tolower(word[i]); // Append Character in Lowercase

  return wordToLower;
}