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

// --- Functions

// Function to Stop the Program Flow while the User doesn't press the ENTER key
void pressEnterToCont(string message, bool warning = false)
{
  string _;

  printTitle(message, warning);
  getline(cin, _);
  // ignoreInput();
}