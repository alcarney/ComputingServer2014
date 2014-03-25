#ifndef PYTHON_UI_C
#define PYTHON_UI_C

#include "server_utils.h"

struct account
{
    char* username;
    char* password;
};
int handleUI(int their_socket);
int loginSuccesful();                          // User login function

#endif
