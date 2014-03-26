#ifndef PYTHON_UI_C
#define PYTHON_UI_C

#include <string.h>
#include "server_utils.h"

struct account
{
    char*  username;
    char*  password;
};
int handleUI(int their_socket);

// Login Functions
int loginSuccesful();                          // Main login function

// Text file parsing functions
int getNumLines(FILE* file);

#endif
