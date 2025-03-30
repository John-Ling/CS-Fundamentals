#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"
#include "utils.h"

int main(int argc, char* argv[])
{
    HashType type = STRING;
    HashTable* table = LibHashTable.create(type, 10, sizeof(int));
    if (table == NULL) 
    {
        puts("Not ta daa");
        return EXIT_FAILURE;
    }

    LibHashTable.free(table, default_free);

    return EXIT_SUCCESS;
}