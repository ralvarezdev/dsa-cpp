#include <string>
#include <iostream>

#include "../namespaces.h"
#include "ansiEsc.h"

using std::cin;
using std::getline;
using std::string;

using namespace terminal;

// --- Function Prototypes
void pressEnterToCont(string message, bool warning);
string getLower(string word);

// --- Functions

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