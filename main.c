#include "util/socketutil.h"

#define PORT 8000
#define IP_ADDRESS "192.168.21.222"

int main()
{
    setvbuf(stdout, NULL, _IOLBF, 0);
    // srand(time(0)); // let's set the seed with unix timestamp
    int serverSocketFD = createTCPScoketIPv4();

    struct sockaddr_in *serverAddress = createIPv4Address(IP_ADDRESS, PORT);

    int result = bind(serverSocketFD, serverAddress, sizeof(*serverAddress));
    if (result == 0)
        printf("socket was bound successfully\n");

    int listenResult = listen(serverSocketFD, 10);
    if (result == 0)
        printf("successfully listening...\n");

    startAcceptingIncomingConnections(serverSocketFD);

    shutdown(serverSocketFD, SHUT_RDWR);

    return 0;
}
