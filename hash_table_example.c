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
    // int b = 5;
    LibHashTable.insert_str(table, "Hello World", &a);
    a = a + 4;
    LibHashTable.insert_str(table, "Hello World", &a);
    a = 234;
    LibHashTable.insert_str(table, "Hello world", &a);
    a = 11;
    LibHashTable.insert_str(table, "Hello Wofeafwald", &a);
    LibHashTable.insert_str(table, "Hello Worl3d", &a);
    a = 43;
    LibHashTable.insert_str(table, "Hello sorld", &a);

    LibHashTable.print_keys(table, print_key_str);

    puts("Retrieving Hello World");
    // KeyValue* c = LibHashTable.get_str(table, "Hello World");
    KeyValue* c = ht_get_str(table, "Hello World");
    puts("Retrieval Success");
    
    if (c == NULL)
    {
        puts("error");
    }
    else
    {
    printf("%d\n", *(int*)c->data);
    }

    puts("Retrieving Hello sorld");
    c = LibHashTable.get_str(table, "Hello sorld");
    puts("Retrieval Success");

    if (c == NULL)
    {
        puts("error");
    }
    else
    {
        printf("%d\n", *(int*)c->data);
    }

    puts("Deleting Hello World");
    LibHashTable.delete_str(table, "Hello World", free);

    
    puts("Deleting Hello world");
    LibHashTable.delete_str(table, "Hello world", free);


    puts("Testing deletion of non existent item");
    if (LibHashTable.delete_str(table, "Hello world", free)  == EXIT_FAILURE)
    {
        puts("Correct");
    }

    LibHashTable.print_keys(table, print_key_str);

    puts("Deleting Hello sorld");
    printf("%d\n", LibHashTable.delete_str(table, "Hello sorld", free));
    
    LibHashTable.print_keys(table, print_key_str);

    LibHashTable.insert_str(table, "Hello world", &a);
    LibHashTable.insert_str(table, "Hello world", &a);
    LibHashTable.insert_str(table, "Hello world", &a);
    LibHashTable.insert_str(table, "Hello world", &a);

    c = LibHashTable.get_str(table, "Hello World");

    if (c == NULL)
    {
        puts("error");
    }
    else
    {
        printf("%d\n", *(int*)c->data);
    }
    
    puts("Final");


    LibHashTable.print_keys(table, print_key_str);

    LibHashTable.free(table, free);
    return EXIT_SUCCESS;
}