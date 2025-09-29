#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"
#include "utils.h"

int string_test(void);
int int_test(void);

void print_key_str(const void* data)
{
    if (data == NULL)
    {
        puts("Data is NULL");
        return;
    }
    KeyValue* pair = (KeyValue*)data;

    printf("%s ", (char*)pair->key);
    return;
}

void print_key_int(const void* data)
{
    if (data == NULL)
    {
        return;
    }

    KeyValue* pair = (KeyValue*)data;
    printf("%d ", *(int*)pair->key);
    return;
}

int main(void)
{
    HashTable* table = LibHashTable.create(STRING, 10, sizeof(int));
    // int a = 5;
    // LibHashTable.insert_str(table, "test", &a);
    // LibHashTable.insert_str(table, "tes", &a);
    // LibHashTable.insert_str(table, "fasdfas", &a);
    // LibHashTable.insert_str(table, "tasfaf", &a);
    // LibHashTable.print_keys(table, print_key_int);

    int a = 5;
    // int b = 5;
    LibHashTable.insert_str(table, "Hello World", &a);
    // LibHashTable.insert_str(table, "Hello", &a);
    LibHashTable.insert_str(table, "Hello World", &a);

    puts("RUNNING STRING TEST");
    string_test();
    // puts("RUNNING INT TEST");
    // int_test();    

    LibHashTable.free(table, free);
    return EXIT_SUCCESS;
}

int int_test(void)
{
    HashType type = INT;
    HashTable* table = LibHashTable.create(type, 10, sizeof(int));

    if (table == NULL)
    {
        puts("Not ta daa");
        return EXIT_FAILURE;
    }

    int b = 234;

    LibHashTable.insert_int(table, 1, &b);
    LibHashTable.insert_int(table, 2323, &b);
    LibHashTable.insert_int(table, 2, &b);
    LibHashTable.insert_int(table, 3, &b);

    LibHashTable.print_keys(table, print_key_int);

    LibHashTable.delete_int(table, 2, free);
    
    puts("Checking deletion of non-existent key");
    if (LibHashTable.delete_int(table, 2, free) == EXIT_FAILURE)
    {
        puts("Correct");
    }
    else
    {
        puts("Failed");
    }

    LibHashTable.print_keys(table, print_key_int);

    puts("Checking retrieval");
    void* c = LibHashTable.get_int(table, 3);

    if (c == NULL)
    {
        puts("Failed");
    }
    else
    {
        printf("%d\n", *(int*)c);
    }

    puts("Testing retrieval for non existent key");
    if (LibHashTable.get_int(table, 3) == NULL)
    {
        puts("Correct");
    }

    puts("Freeing");
    LibHashTable.free(table, free);

    return EXIT_SUCCESS;
}

int string_test(void)
{
    HashType type = STRING;
    HashTable* table = LibHashTable.create(type, 10, sizeof(int));
    if (table == NULL) 
    {
        puts("Not ta daa");
        return EXIT_FAILURE;
    }

    int a = 5;
    for (char c = 'a'; c <= 'z'; c++)
    {
        LibHashTable.insert_chr(table, c, &a);
    }
    puts("Passed");

    LibHashTable.print_keys(table, print_key_str);

    for (char c = 'a'; c <= 'z'; c++)
    {
        assert(LibHashTable.get_chr(table, c) != NULL);
    }

    puts("Passed");

    for (char c = 'a'; c <= 'z'; c++)
    {
        LibHashTable.delete_chr(table, c, free);
    }

    LibHashTable.print_keys(table, print_key_str);

    LibHashTable.free(table, free);
    return EXIT_SUCCESS;
}
