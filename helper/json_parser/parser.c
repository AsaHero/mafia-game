#include <stdlib.h>
#include <string.h>
#include <jansson.h>

int main()
{
    char *buffer = "{\"name\":\"Asad\",\"age\":5,\"friend\":{\"friend_name\":\"Sanjar\"}}";

    json_t *data;
    json_error_t error;

    data = json_loads(buffer, 0, &error);

    if (!data)
    {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return 1;
    }

    json_t *name, *age, *friend, *friend_name;

    if (!json_is_object(data))
    {
        fprintf(stderr, "error: data is not an object\n");
        json_decref(data);
        return 1;
    }

    name = json_object_get(data, "name");
    if (!json_is_string(name))
    {
        fprintf(stderr, "error: name is not a string\n");
        json_decref(data);
        return 1;
    }

    age = json_object_get(data, "age");
    if (!json_is_integer(age))
    {
        fprintf(stderr, "error: age is not an integer\n");
        json_decref(data);
        return 1;
    }

    friend = json_object_get(data, "friend");
    if (!json_is_object(friend))
    {
        fprintf(stderr, "error: friend is not a object\n");
        json_decref(data);
        return 1;
    }

    friend_name = json_object_get(friend, "friend_name");
    if (!json_is_string(friend_name))
    {
        fprintf(stderr, "error: commit %d: message is not a string\n");
        json_decref(data);
        return 1;
    }
    
    printf("%s, %lld, %s", json_string_value(name), json_integer_value(age), json_string_value(friend_name));


    json_decref(data);
    return 0;
}