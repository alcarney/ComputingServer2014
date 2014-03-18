#include "server_utils.h"

int main()
{
    int sock = new_socket(3490);
    int rv = run_server(sock);

    return 0;
}
