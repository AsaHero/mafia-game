#include <jansson.h>
#include <stdbool.h>

enum Actions
{
    Vote,
    Kill,
    Heal,
    Check,
};

struct Lobby
{
    char *LobbyID;
    char *host;
    int numberOfPlayers;
    int playersSocketFD[10];
    int userIdList[10];
};


struct PlayerSocket
{
    int playerSocketFD;
    struct sockaddr_in address;
    int error;
    bool acceptedSuccessfully;
};


struct GetLobbiesRequest
{
    json_t *event;
};

struct GetLobbiesResponse
{
    json_t *event;
    json_t *data;
    json_t *name;
    json_t *id;
    json_t *playersCount;
    json_t *host;
};

struct CreateLobbyRequest
{
    json_t *event;
    json_t *data;
    json_t *id;
    json_t *username;
    json_t *lobbyName;
};

struct CreateLobbyRequestModel
{
    char *id;
    char *username;
    char *lobbyName;
};

struct CreateLobbyResponse
{
    json_t *event;
    json_t *data;
    json_t *id;
    json_t *name;
    json_t *host;
    json_t *playersCount;
};

struct JoinLobbyRequest
{
    json_t *event;
    json_t *data;
    json_t *id;
    json_t *username;
    json_t *lobbyId;
};

struct JoinLobbyRequestModel
{
    char *id;
    char *username;
    char *lobbyId;
};

struct JoinLobbyResponse
{
    json_t *event;
    json_t *data;
    json_t *id;
    json_t *name;
    json_t *playersCount;
    json_t *host;
    json_t *players;
    json_t *playersId;
    json_t *playersUsername;
};

struct SomeoneJoinedLobbyResponse
{
    json_t *event;
    json_t *data;
    json_t *id;
    json_t *username;
};

struct SomeoneLeftLobbyResponse
{
    json_t *event;
    json_t *data;
    json_t *id;
    json_t *username;
};

struct LeaveLobbyRequest
{
    json_t *event;
    json_t *data;
    json_t *id;
    json_t *username;
    json_t *lobbyId;
};

struct LeaveLobbyResponse
{
    json_t *event;
    json_t *data;
};

struct StartGameRequest
{
    json_t *event;
    json_t *data;
    json_t *lobbyId;
};

struct StartGameResponse
{
    json_t *event;
    json_t *data;
    json_t *role;
};

struct GameMessageRequest
{
    json_t *event;
    json_t *data;
    json_t *lobbyId;
    json_t *id;
    json_t *username;
    json_t *message;
    json_t *isPrivate;
};

struct GameMessageRequestModel
{
    char *lobbyId;
    char *id;
    char *username;
    char *message;
    bool isPrivate;
};

struct GameMessageResponse
{
    json_t *event;
    json_t *data;
    json_t *id;
    json_t *username;
    json_t *message;
};

struct GameVoteRequest
{
    json_t *event;
    json_t *data;
    json_t *lobbyId;
    json_t *id;
    json_t *username;
    json_t *player;
};

struct GameVoteResponse
{
    json_t *event;
    json_t *data;
    json_t *username;
    json_t *player;
};

struct GameVoteResultRequest
{
    json_t *event;
    json_t *data;
};

struct GameVoteResultResponse
{
    json_t *event;
    json_t *data;
    json_t *username;
    json_t *role;
};

struct GameActionRequest
{
    json_t *event;
    json_t *data;
    json_t *lobbyId;
    json_t *id;
    json_t *username;
    json_t *action;
    json_t *player;
};

struct GameActionResponse
{
    json_t *event;
    json_t *data;
    json_t *action;
    json_t *player;
    json_t *role;
};

struct GameActionResultRequest
{
    json_t *event;
    json_t *data;
};

struct GameActionResultResponse
{
    json_t *event;
    json_t *data;
    json_t *killed;
    json_t *role;
    json_t *shot;
};