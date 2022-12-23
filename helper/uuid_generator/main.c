#include <uuid/uuid.h>
#include <stdio.h>


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

int main() 
{
    char *guid = generateUUID();
    printf(guid);
    return 0;
}