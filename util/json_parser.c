#include "socketutil.h"

char *parseEvent(char *buffer)
{
    json_t *data;
    json_error_t error;

    data = json_loads(buffer, 0, &error);

    if (!data)
    {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return NULL;
    }

    if (!json_is_object(data))
    {
        fprintf(stderr, "error: data is not an object\n");
        json_decref(data);
        return NULL;
    }

    json_t *event;

    event = json_object_get(data, "event");
    if (!json_is_string(event))
    {
        fprintf(stderr, "error: event is not a string\n");
        json_decref(data);
        return NULL;
    }

    char *event_text = json_string_value(event);
    char *response = malloc(sizeof(event_text));
    strcpy(response, event_text);

    printf("event:// %s\n", response);

    json_decref(data);
    return response;
}

struct CreateLobbyRequestModel *parseCreateLobbyRequest(char *buffer)
{
    struct CreateLobbyRequest request;
    struct CreateLobbyRequestModel *requestModel = malloc(sizeof(struct CreateLobbyRequestModel));
    json_t *root;
    json_error_t error;

    root = json_loads(buffer, 0, &error);

    if (!root)
    {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return NULL;
    }

    request.data = json_object_get(root, "data");
    if (!json_is_object(request.data))
    {
        fprintf(stderr, "error: request.data is not a object\n");
        json_decref(root);
        return NULL;
    }

    request.id = json_object_get(request.data, "id");
    if (!json_is_string(request.id))
    {
        fprintf(stderr, "error: id is not a string\n");
        json_decref(root);
        return NULL;
    }

    request.username = json_object_get(request.data, "username");
    if (!json_is_string(request.username))
    {
        fprintf(stderr, "error: username is not a string\n");
        json_decref(root);
        return NULL;
    }

    request.lobbyName = json_object_get(request.data, "lobbyName");
    if (!json_is_string(request.lobbyName))
    {
        fprintf(stderr, "error: lobbyName is not a string\n");
        json_decref(root);
        return NULL;
    }



    // requestModel->id = malloc(sizeof(json_string_value(request.id)));
    // requestModel->username = malloc(sizeof(json_string_value(request.username)));
    // requestModel->lobbyName = malloc(sizeof(json_string_value(request.lobbyName)));

    // strcpy(requestModel->id, json_string_value(request.id));
    // strcpy(requestModel->username, json_string_value(request.username));
    // strcpy(requestModel->lobbyName, json_string_value(request.lobbyName));

    requestModel->id = "123456";
    requestModel->username = "A_Abdurakhimov";
    requestModel->lobbyName = "AzizLobby";

    json_decref(root);
    return requestModel;
}

struct GameMessageRequestModel *parseGameMessageRequest(char *buffer)
{
    struct GameMessageRequest request;
    struct GameMessageRequestModel *requestModel = malloc(sizeof(struct GameMessageRequestModel));
    json_t *root;
    json_error_t error;

    root = json_loads(buffer, 0, &error);

    if (!root)
    {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return requestModel;
    }

    request.data = json_object_get(root, "data");
    if (!json_is_object(request.data))
    {
        fprintf(stderr, "error: request.data is not a object\n");
        json_decref(root);
        return requestModel;
    }

    request.id = json_object_get(request.data, "id");
    if (!json_is_string(request.id))
    {
        fprintf(stderr, "error: id is not a string\n");
        json_decref(root);
        return requestModel;
    }

    request.username = json_object_get(request.data, "username");
    if (!json_is_string(request.username))
    {
        fprintf(stderr, "error: username is not a string\n");
        json_decref(root);
        return requestModel;
    }

    request.lobbyId = json_object_get(request.data, "lobbyId");
    if (!json_is_string(request.lobbyId))
    {
        fprintf(stderr, "error: lobbyName is not a string\n");
        json_decref(root);
        return requestModel;
    }

    request.isPrivate = json_object_get(request.data, "isPrivate");
    if (!json_is_boolean(request.isPrivate))
    {
        fprintf(stderr, "error: isPrivate is not a bool\n");
        json_decref(root);
        return requestModel;
    }

    requestModel->id = malloc(sizeof(json_string_value(request.id)));
    requestModel->username = malloc(sizeof(json_string_value(request.username)));
    requestModel->lobbyId = malloc(sizeof(json_string_value(request.lobbyId)));
    requestModel->isPrivate = malloc(sizeof(json_string_value(request.isPrivate)));

    strcpy(requestModel->id ,json_string_value(request.id));
    strcpy(requestModel->username, json_string_value(request.username));
    strcpy(requestModel->lobbyId, json_string_value(request.lobbyId));
    requestModel->isPrivate = json_boolean_value(request.isPrivate); 


    json_decref(root);
    return requestModel;
}

struct JoinLobbyRequestModel *parseJoinLobbyRequest(char *buffer)
{
    struct JoinLobbyRequest request;
    struct JoinLobbyRequestModel *requestModel = malloc(sizeof(struct JoinLobbyRequestModel));
    json_t *root;
    json_error_t error;

    root = json_loads(buffer, 0, &error);

    if (!root)
    {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return NULL;
    }

    request.data = json_object_get(root, "data");
    if (!json_is_object(request.data))
    {
        fprintf(stderr, "error: request.data is not a object\n");
        json_decref(root);
        return NULL;
    }

    request.id = json_object_get(request.data, "id");
    if (!json_is_string(request.id))
    {
        fprintf(stderr, "error: id is not a string\n");
        json_decref(root);
        return NULL;
    }

    request.username = json_object_get(request.data, "username");
    if (!json_is_string(request.username))
    {
        fprintf(stderr, "error: username is not a string\n");
        json_decref(root);
        return NULL;
    }

    request.lobbyId = json_object_get(request.data, "lobbyId");
    if (!json_is_string(request.lobbyId))
    {
        fprintf(stderr, "error: lobbyName is not a string\n");
        json_decref(root);
        return NULL;
    }
    requestModel->id = malloc(sizeof(json_string_value(request.id)));
    requestModel->username = malloc(sizeof(json_string_value(request.username)));
    requestModel->lobbyId = malloc(sizeof(json_string_value(request.lobbyId)));

    strcpy(requestModel->id, json_string_value(request.id));
    strcpy(requestModel->username, json_string_value(request.username));
    strcpy(requestModel->lobbyId, json_string_value(request.lobbyId));

    json_decref(root);
    return requestModel;
}
