#ifndef SERVER_C
#define SERVER_C

#include "server_utils.h"
#include "python_ui.h"

struct taskRequest
{
    int clientType;
    int taskType;
}; 

int run_server(int sock);

#endif
