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
string getString(string askMessage, char restrictions[], int length, string errMessage);

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

      stream << "The Number is Out of Range"
             << " [" << low << '-' << high << "]";

      pressEnterToCont(stream.str(), true);
    }
}

// Function to Ask for String with Some Restrictions
string getString(string askMessage, char restrictions[], int length, string errMessage)
{
  string input;

  // Ask for String Input
  while (true)
    try
    {
      cout << askMessage << ": ";
      getline(cin, input);

      // Input Can't Contain Any Restricted Character
      for (int n = length; n > 0; n--)
        if (input.find(restrictions[n - 1]) != string::npos)
          throw(-1);

      return input;
    }
    catch (...)
    {
      printTitle(errMessage, true); // Ignore String if it Contains Any Restricted Character
      cout << '\n';
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