/**********************************************\
* clear_term.cpp                  vector adder *
* Caleb Everett                        statics *
*                                              *
* clears the terminal                          *
* individual methods not written by me         *
* found on cplusplus.com                       *
\**********************************************/
#if !defined CLEAR_TERM_CPP
#define CLEAR_TERM_CPP

#include "clear_term.h"

#if defined _WIN32 || defined _WIN64
// this method used in windows
// writes blank charecters to every cell in the terminal and moves
// the cursor to the top left corner
  void ClearScreen()
  {
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
          hStdOut,
          (TCHAR) ' ',
          cellCount,
          homeCoords,
          &count
          )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
          hStdOut,
          csbi.wAttributes,
          cellCount,
          homeCoords,
          &count
          )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition( hStdOut, homeCoords );
  }
#elif defined __linux__
// this method used in posix (linux, mac, ect)
// issues terminal clear command
  void ClearScreen() {
    if (!cur_term) {
      int result;
      setupterm( NULL, STDOUT_FILENO, &result );
      if (result <= 0) return;
    }

    putp( tigetstr( (char*)"clear" ) );
  }
#else
  void ClearScreen() {
    ;
  }
#endif

#endif
