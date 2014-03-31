#ifndef PYTHON_UI_C
#define PYTHON_UI_C

#include <string.h>
#include "server_utils.h"

// Task Types
const int LOGIN = 0;
const int SALES = 1;

struct account
{
    char*  username;
    char*  password;
};

struct task
{
    int clientType;
    int taskType;
};

int handleUI(int their_socket, int task);

// Login Functions
int loginSuccesful(int their_socket);                          // Main login function

// Text file parsing functions
int getNumLines(FILE* file);
int loadAccounts(FILE* file, struct account* accounts, int num);

#endif
