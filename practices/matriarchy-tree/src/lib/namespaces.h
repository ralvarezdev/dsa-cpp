#include <string>

using std::string;

#ifndef NAMESPACES_H
#define NAMESPACES_H

namespace files
{
  const char sep = ','; // Separators
  const int newLine = '\n';
}

namespace terminal
{
  // - ANSI Escape Code
  const string reset = "\x1b[0m"; // Reset Terminal Text Format to Default
  const string clear = "\033c";   // Clear Terminal

  // - Format Constants
  const string tab1 = string(3, ' '); // String with 3 whitespaces
  const string tab2 = string(8, ' '); // String with 8 whitespaces
  const bool applyBg = true;          // Add Customed Background Color
  const bool applyFg = true;          // Add Customed Foreground Color

  // --- Color Command Created Using ralvarezdev's Minigrep. URL: https://github.com/ralvarezdev/minigrep

  // - Normal State
  const string sgrBg = "\x1b[48;2;153;204;255m"; // Command to Change Text Background Color
  const string sgrFg = "\x1b[38;2;32;32;32m";    // Command to Change Text Foreground Color

  // - Warning (On Error)
  const string sgrBgError = "\x1b[48;2;255;153;153m";
  const string sgrFgError = "\x1b[38;2;32;32;32m";

  // - Number of Characters
  const int nChar = 100; // Max Number of Characters being Printed on Each Line
  const int nLevel = 10;
  const int nMotherId = 10;
  const int nNodeId = 10;
  const int nName = 20;
  const int nGender = 10;
  const int nStatus = 10;
  const int nConsanguinity = 15;
}

namespace matrPerson
{
  // NOTE: Please, don't Judge me by the Genders. These are just Requirements that I received. I'm not Against the LGBTQ+ Community
  // - Genders
  enum genders
  {
    woman,
    man,
    genderNull,
  };

  // - Level Order Traversals
  enum traversals
  {
    parents,
    women,
    men,
    single,
    cousins
  };

  // - Married Statuses Abbreviations
  const int singleAbbr = 'S';
  const int marriedAbbr = 'M';

  // - Gender Abbreviations
  const int womanAbbr = 'W';
  const int manAbbr = 'M';

  // - Consanguinity Abbreviations
  const int consanguinityAbbr = 'Y';
  const int affinityAbbr = 'N';
}

#endif