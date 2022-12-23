#include "socketutil.h"

// All actions
char *actoinList[4] = {"vote", "kill", "heal", "check"};

struct Lobby newLobby;

char *generateUUID()
{
    uuid_t binuuid;
    /*
     * Generate a UUID. We're not done yet, though,
     * for the UUID generated is in binary format
     * (hence the variable name). We must 'unparse'
     * binuuid to get a usable 36-character string.
     */
    uuid_generate_random(binuuid);

    /*
     * uuid_unparse() doesn't allocate memory for itself, so do that with
     * malloc(). 37 is the length of a UUID (36 characters), plus '\0'.
     */
    char *uuid = malloc(37);

    /* Produces a UUID string at uuid consisting of lower case letters. */
    uuid_unparse_lower(binuuid, uuid);

    return uuid;
}

int createTCPScoketIPv4()
{
    // Socket creation
    // AF_INET = IPv4
    // SOCK_STREAM = TCP
    return socket(AF_INET, SOCK_STREAM, 0);
}

struct sockaddr_in *createIPv4Address(char *ip, unsigned int port)
{
    // specifying the address sockaddr_in = IPv4 and sockaddr_in6 = IPv6
    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    if (ip == "localhost" || ip == "")
        address->sin_addr.s_addr = INADDR_ANY;
    else
        inet_pton(AF_INET, ip, &address->sin_addr.s_addr);

    return address;
}

struct PlayerSocket *acceptIncomingConnections(int serverSocketFD)
{
    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(struct sockaddr_in);
    int clientSocketFD = accept(serverSocketFD, &clientAddress, &clientAddressSize);

    struct PlayerSocket *acceptedPlayer = malloc(sizeof(struct PlayerSocket));
    acceptedPlayer->address = clientAddress;
    acceptedPlayer->playerSocketFD = clientSocketFD;
    acceptedPlayer->acceptedSuccessfully = clientSocketFD > 0;
    if (acceptedPlayer->acceptedSuccessfully)
        acceptedPlayer->error = clientSocketFD;

    send(clientSocketFD, "Hello Aziz!!!", 14, 0);

    return acceptedPlayer;
}

void startReceiveIncomingDataOnTheard(struct PlayerSocket *acceptedPlayer)
{
    pthread_t id;
    pthread_create(&id, NULL, receiveIncomingData, acceptedPlayer);
}

void receiveIncomingData(struct PlayerSocket *player)
{
    char buffer[1024];

    while (true)
    {
        int amountReceived = recv(player->playerSocketFD, buffer, 1024, 0);

        if (amountReceived > 0)
        {
            buffer[amountReceived] = '\0';
            handleRequest(player, buffer);
        }

        if (amountReceived <= 0)
            break;
    }
    close(player->playerSocketFD);
}

void startAcceptingIncomingConnections(int serverSocketFD)
{
    while (true)
    {
        struct PlayerSocket *acceptedPlayer = acceptIncomingConnections(serverSocketFD);
        printf("%lld sfd client is connected...\n", acceptedPlayer->playerSocketFD);
        startReceiveIncomingDataOnTheard(acceptedPlayer);
    }
}

void LobbyList(struct PlayerSocket *player)
{
    char response[1024];

    sprintf(response, "{ \"event\": \"lobby-list\", \"data\": [{\"name\":\"%s\", \"id\":\"%s\", \"playersCount\": %d, \"host\": \"%s\"}]}\0", "AzizLobby", "123456", newLobby.numberOfPlayers, "Aziz");

    send(player->playerSocketFD, response, sizeof(response), 0);
}

void LobbyCreate(struct PlayerSocket *player, char *buffer)
{
    struct CreateLobbyRequestModel *res = parseCreateLobbyRequest(buffer);
    newLobby.host = res->username;
    newLobby.LobbyID = generateUUID();
    newLobby.playersSocketFD[0] = player->playerSocketFD;
    newLobby.userIdList[0] = res->id;
    char response[1024];
    sprintf(response, "{\"event\":\"lobby-create\", \"data\":{\"id\":\"%s\", \"name\":\"%s\", \"host\":\"%s\", \"playersCount\": 1}}\0", newLobby.LobbyID, res->lobbyName, res->username);
    send(newLobby.playersSocketFD[0], response, sizeof(response), 0);
}

void LobbyJoin(struct PlayerSocket *player, char *buffer)
{
    struct JoinLobbyRequestModel *res = parseJoinLobbyRequest(buffer);
    if (newLobby.numberOfPlayers < 10)
    {
        newLobby.numberOfPlayers++;
        newLobby.playersSocketFD[newLobby.numberOfPlayers - 1] = player->playerSocketFD;
        newLobby.userIdList[newLobby.numberOfPlayers - 1] = res->id;
    }

    // char response[1024];

    // char* player_object = "{\"id\": \"%s\", \"username\":\"%s\"}";
    // char* player_list = "{\"id\": \"%s\", \"username\":\"%s\"}";
    // for (int i =1; i < newLobby.numberOfPlayers; i++)
    // {
    //     strcat(player_list, ",");
    //     strcat(player_list, player_object);
    // }

    // sprintf(response, "{\"event\":\"lobby-join\", \"data\": {\"name\":\"%s\", \"playersCount\": %d, \"host\":\"%s\", \"players\": [%s]}}", "", newLobby.numberOfPlayers, newLobby.host, player_list);
    // sprintf(response, response, "")
}

void LobbyLeave(struct PlayerSocket *player, char *buffer)
{
}

void GameStart(struct PlayerSocket *player, char *buffer)
{
}

void GameMessage(struct PlayerSocket *player, char *buffer)
{
    struct GameMessageRequestModel *res = parseGameMessageRequest(buffer);
    char response[1024];
    sprintf(response, "{\"event\": \"game-message\",\"data\": {\"id\": \"%s\",\"username\": \"%s\",\"message\": \"%s\"}}\0", res->id, res->username, res->message);
    for (int i = 0; i < newLobby.numberOfPlayers; i++)
    {
        send(newLobby.playersSocketFD[i], response, sizeof(response), 0);
    }
}

void GameVote(struct PlayerSocket *player, char *buffer)
{
}

void GameVoteResult(struct PlayerSocket *player, char *buffer)
{
}

void GameAction(struct PlayerSocket *player, char *buffer)
{
}

void GameActionResult(struct PlayerSocket *player, char *buffer)
{
}

void handleRequest(struct PlayerSocket *player, char *buffer)
{
    printf("Request:// %s\n", buffer);
    char *event = parseEvent(buffer);
    printf("event:// %s\n", event);
    if (!strcmp(event, "lobby-list"))
    {
        LobbyList(player);
    }
    else if (!strcmp(event, "lobby-create"))
    {
        LobbyCreate(player, buffer);
    }
    else if (!strcmp(event, "lobby-join"))
    {
        LobbyJoin(player, buffer);
    }
    else if (!strcmp(event, "lobby-leave"))
    {
    }
    else if (!strcmp(event, "game-start"))
    {
    }
    else if (!strcmp(event, "game-message"))
    {
        GameMessage(player, buffer);
    }
    else if (!strcmp(event, "game-vote"))
    {
    }
    else if (!strcmp(event, "game-vote-result"))
    {
    }
    else if (!strcmp(event, "game-action"))
    {
    }
    else if (!strcmp(event, "game-action-result"))
    {
    }
}