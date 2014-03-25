#ifndef PYTHON_UI_C
#define PYTHON_UI_C

#include "server_utils.h"

struct account
{
    char [32] username;
    char [32] password;
};
int handleUI(int their_socket);
int loginSuccesful();                          // User login function

#endif
