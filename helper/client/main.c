#include "../util/socketutil.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PORT 8080
#define IP_ADDRESS "localhost"

int main()
{

    int socketFD = createTCPScoketIPv4();

    struct sockaddr_in *address = createIPv4Address(IP_ADDRESS, PORT);

    // with this created socket we can connect() to other remote sockets
    int result = connect(socketFD, address, sizeof(*address));
    if (result == 0)
        printf("connection was successful\n");

    char *line = NULL;
    size_t lineSize = 0;
    printf("type your message to group(or exit to close)\n");

    while (true)
    {
        ssize_t charCount = getline(&line, &lineSize, stdin);
        if (charCount > 0)
        {
            if (strcmp(line, "exit\n") == 0)
                break;
            ssize_t amountSent = send(socketFD, line, charCount, 0);
        }
    }

    return 0;
}