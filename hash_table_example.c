#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"
#include "utils.h"

void print_key(const void* data)
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

int main(void)
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

    for (int i = 0; i < table->bucketCount; i++)
    {
        if (table->buckets[i]->head == NULL)
        {
            puts("NOTHING HERE");
            continue;
        }
        LibLinkedList.print(table->buckets[i], print_key);
    }

    void* c = LibHashTable.get_str(table, "Hello World");

    if (c == NULL)
    {
        puts("error");
    }
    else
    {
        printf("%d\n", *(int*)c);
    }

    c = LibHashTable.get_str(table, "Hello sorld");

    if (c == NULL)
    {
        puts("error");
    }
    else
    {
        printf("%d\n", *(int*)c);
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

    for (int i = 0; i < table->bucketCount; i++)
    {
        if (table->buckets[i]->head == NULL)
        {
            puts("NOTHING HERE");
            continue;
        }
        LibLinkedList.print(table->buckets[i], print_key);
    }


    puts("Deleting Hello sorld");
    printf("%d\n", LibHashTable.delete_str(table, "Hello sorld", free));
    

    for (int i = 0; i < table->bucketCount; i++)
    {
        if (table->buckets[i]->head == NULL)
        {
            puts("NOTHING HERE");
            continue;
        }
        LibLinkedList.print(table->buckets[i], print_key);
    }

    LibHashTable.insert_str(table, "Hello world", &a);
    LibHashTable.insert_str(table, "Hello world", &a);
    LibHashTable.insert_str(table, "Hello world", &a);
    LibHashTable.insert_str(table, "Hello world", &a);
    LibHashTable.insert_str(table, "Hello world", &a);
    
    puts("Final");

    for (int i = 0; i < table->bucketCount; i++)
    {
        if (table->buckets[i]->head == NULL)
        {
            puts("NOTHING HERE");
            continue;
        }
        LibLinkedList.print(table->buckets[i], print_key);
    }

    puts("Running free");
    LibHashTable.free(table, default_free);

    return EXIT_SUCCESS;
}