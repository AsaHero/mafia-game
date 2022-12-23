#ifndef SOCKETUTIL_F
#define SOCKETUTIL_F

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <uuid/uuid.h>
#include <jansson.h>
#include "models.h"

// special
char *generateUUID();

// socket functions
int createTCPScoketIPv4();
struct sockaddr_in *createIPv4Address(char *ip, unsigned int port);
struct PlayerSocket *acceptIncomingConnections(int serverClientFD);
void startAcceptingIncomingConnections(int serverSocketFD);
void startReceiveIncomingDataOnTheard(struct PlayerSocket *acceptedPlayer);
void receiveIncomingData(struct PlayerSocket *player);

// logic
void handleRequest(struct PlayerSocket *player, char *buffer);

// parsers
char *parseEvent(char *buffer);
struct CreateLobbyRequestModel *parseCreateLobbyRequest(char *buffer);
struct JoinLobbyRequestModel *parseJoinLobbyRequest(char *buffer);
struct GameMessageRequestModel *parseGameMessageRequest(char *buffer);

#endif // SOCKETUTIL_F