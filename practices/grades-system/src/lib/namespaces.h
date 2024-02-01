#include <string>

using std::string;

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
  const string sgrBg = "\x1b[48;2;153;204;255";  // Command to Change Text Background Color
  const string sgrFgCmd = "\x1b[38;2;32;32;32m"; // Command to Change Text Foreground Color

  // - Warning (On Error)
  const string sgrBgError = "\x1b[48;2;255;153;153m";
  const string sgrFgError = "\x1b[38;2;32;32;32m";

  // - Number of Characters
  const int nChar = 100; // Max Number of Characters being Printed on Each Line
  const int id = 5;
  const int firstName = 12;
  const int lastName = 12;
  const int email = 12;
  const int gender = 8;
  const int course = 5;
}

namespace students
{ // Enums Should be at the Beginning
  // - Genders
  enum genders
  {
    female,
    male,
    nonBinary // To get the number of Fields. SHOULD BE AT THE END
  };
}