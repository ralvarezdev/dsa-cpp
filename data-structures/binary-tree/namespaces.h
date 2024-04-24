#include <string>
#include <iostream>
#include <sstream>

using std::cin;
using std::cout;
using std::getline;
using std::ostringstream;
using std::string;

#ifndef BIN_TREE_NAMESPACES_H
#define BIN_TREE_NAMESPACES_H

namespace binaryTree
{
  // Terminal-related Constants
  const string clear = "\033c"; // Clear Terminal

  // --- Functions Prototypes
  void pressEnterToCont(string message);
  bool booleanQuestion(string message);
  int getChar(string askMessage, int whitelist[], int length, string errMessage);

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
      pressEnterToCont("ERROR: It's a Yes/No Question. You must type 'y', 'Y' or 'n', 'N'");
    }
  }

  // Function to Stop the Program Flow while the User doesn't press the ENTER key
  void pressEnterToCont(string message)
  {
    string _;

    cout << message << ": ";
    getline(cin, _);
  }

  // Function to Get Character
  int getChar(string askMessage, int whitelist[], int length, string errMessage)
  {
    string input;
    int c;

    // Ask for String Input
    while (true)
      try
      {
        cout << askMessage << ": ";
        getline(cin, input);

        // Get First Character as Lowercase
        c = tolower(input[0]);

        // Input Should be Found in Characters Whitelist
        for (int i = 0; i < length; i++)
          if (whitelist[i] == c)
            return c;

        throw(-1);
      }
      catch (...)
      {
        // Ignore First Character if it's not in Whitelist
        cout << errMessage;
        pressEnterToCont("\nPress ENTER to Continue");
        cout << '\n';
      }
  }
};

#endif