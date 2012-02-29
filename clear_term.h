/**********************************************\
* clear_term.h                    vector adder *
* Caleb Everett                        statics *
*                                              *
* clears the terminal                          *
* Uses different methods for different systems *
* supports windows and linux                   *
* if compiled on another system doesnt do any- *
* thing                                        *
\**********************************************/
#if defined _WIN32 || defined _WIN64
  #include <windows.h>
#elif defined __linux__
  #include <unistd.h>
  #include <term.h>
#endif

void ClearScreen();
