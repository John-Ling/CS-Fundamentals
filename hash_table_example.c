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

    int a = 5;
    int b = 5;
    // LibHashTable.insert_str(table, "Hello World", &a);
    // LibHashTable.insert_str(table, "Hello World", &a);
    // LibHashTable.insert_str(table, "Hello world", &a);
    // LibHashTable.insert_str(table, "Hello Wofeafwald", &a);
    // LibHashTable.insert_str(table, "Hello Worl3d", &a);
    // LibHashTable.insert_str(table, "Hello sorld", &a);

    // void* c = LibHashTable.get_str(table, "Hello World");

    // if (c == NULL)
    // {
    //     puts("error");
    // }
    // else
    // {
    //     printf("%d\n", *(int*)c);
    // }

    // LibHashTable.insert_str(table, "Hello world", &a);
    // LibHashTable.insert_str(table, "Hello world", &a);
    // LibHashTable.insert_str(table, "Hello world", &a);
    // LibHashTable.insert_str(table, "Hello world", &a);
    // LibHashTable.insert_str(table, "Hello world", &a);

    LibHashTable.free(table, default_free);

    return EXIT_SUCCESS;
}