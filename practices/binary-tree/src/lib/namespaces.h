#include <string>

using std::string;

#ifndef NAMESPACES_H
#define NAMESPACES_H

namespace ascii
{
  const int intDiff = 48; // ASCII Code Difference between Chars and Integers
}

namespace terminal
{
  // - ANSI Escape Code
  const string reset = "\x1b[0m"; // Reset Terminal Text Format to Default
  const string clear = "\033c";   // Clear Terminal

  // - Format Constants
  const int nTab1 = 3;
  const string tab1 = string(nTab1, ' '); // String with 3 whitespaces
  const int nTab2 = 8;
  const string tab2 = string(nTab2, ' '); // String with 8 whitespaces
  const bool applyBg = true;              // Add Customed Background Color
  const bool applyFg = true;              // Add Customed Foreground Color

  // --- Color Command Created Using ralvarezdev's Minigrep. URL: https://github.com/ralvarezdev/minigrep

  // - Normal State
  const string sgrBg = "\x1b[48;2;150;242;215m"; // Command to Change Text Background Color
  const string sgrFg = "\x1b[38;2;52;58;64m";    // Command to Change Text Foreground Color

  // - Warning (On Error)
  const string sgrBgError = "\x1b[48;2;255;153;153m";
  const string sgrFgError = "\x1b[38;2;32;32;32m";

  // - Number of Characters
  const int nChar = 100; // Max Number of Characters being Printed on Each Line
}

#endif