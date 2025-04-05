#include <stdio.h>
#include <stdlib.h>

#include "linked_lists.h"
#include "utils.h"

typedef struct KeyValue_t
{
	void* data;
	void* key;
} KeyValue;


void free_pair(void* pair)
{
    KeyValue* freeItem = (KeyValue*)pair;
    free(freeItem->key);
    default_free(freeItem->data);
    free(pair);
    return;
}

// example usage of the linked list library

int main(void)
{
    LinkedList* list = LibLinkedList.create(NULL, 0, sizeof(KeyValue));
    
    for (int i = 0; i < 10; i++)
    {
        KeyValue* pair = (KeyValue*)malloc(sizeof(KeyValue));
        pair->data = (void**)malloc(sizeof(void*));
        pair->key = (void**)malloc(sizeof(void*));

        const char* key = "Hello World";
        int value = 5;

        memcpy(pair->key, (void*)key, sizeof(char*));
        memcpy(pair->data, &value, sizeof(int));
        LibLinkedList.insert(list, (void*)pair, -1);

        free(pair);
    }
    
    // LibLinkedList.insert(list, (void*)pair, -1);
    // LibLinkedList.insert(list, (void*)pair, -1);
    // LibLinkedList.insert(list, (void*)pair, -1);
    // LibLinkedList.insert(list, (void*)pair, -1);
    // LibLinkedList.insert(list, (void*)pair, -1);
    LibLinkedList.free(list, free_pair);
    
    return EXIT_SUCCESS;
}