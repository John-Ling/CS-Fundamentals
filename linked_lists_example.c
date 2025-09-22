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


void print_pair(const void* pair)
{
    KeyValue* converted = (KeyValue*)(pair);
    printf("%d %s\n", *(int*)converted->data, (char*)converted->key);
    return;
}
// example usage of the linked list library

int main(void)
{
    // testing linked list of strings

    LinkedList* list1 = LibLinkedList.create(NULL, 0, sizeof(char*));

    LibLinkedList.insert_str(list1, "Hello World", -1);
    // LibLinkedList.insert_int(list1, 30, 0);
    // LibLinkedList.insert_int(list1, 30, -1);
    // LibLinkedList.insert_int(list1, 30, -1);
    // LibLinkedList.insert_int(list1, 30, -1);
    // LibLinkedList.insert_int(list1, 30, -1);
    // LibLinkedList.insert_str(list1, "Hello World", -1);
    LibLinkedList.insert_str(list1, "Hello World", -1);
    // LibLinkedList.insert_str(list1, "Hello World", -1);
    // LibLinkedList.insert_str(list1, "Hello World", -1);
    LibLinkedList.insert_str(list1, "Jimbob", -1);
    LibLinkedList.insert_str(list1, "Wagwan", -1);

    // LibLinkedList.search_str(list1, "Hello World");

    LibLinkedList.print(list1, print_str);
    char* res = LibLinkedList.search_str(list1, "Jimbob");
    if (res != NULL)
    {
        printf("%s\n", res);
    }
    LibLinkedList.free(list1, free);

    // LinkedList* myList = LibLinkedList.create(NULL, 0, sizeof(int));

    // for (int i = 0; i < 10; i++)
    // {
    //     LibLinkedList.insert_int(myList, i, -1);
    // }

    // LibLinkedList.print(myList, print_int);
    // LibLinkedList.free(myList, free);


    // // testing linked list of user defined structs
    // // in this context these structs will be used as part of a hash table
    // LinkedList* list = LibLinkedList.create(NULL, 0, sizeof(KeyValue));
    
    // for (int i = 0; i < 10; i++)
    // {
    //     KeyValue* pair = (KeyValue*)malloc(sizeof(KeyValue));
    //     pair->data = (void**)malloc(sizeof(void*));
    //     pair->key = (void**)malloc(sizeof(void*));

    //     char* key = "Hello";
    //     int value = 5;

    //     memcpy(pair->key, (void*)key, sizeof(char*));
    //     memcpy(pair->data, &value, sizeof(int));

    //     printf("%s\n", (char*)pair->key);
    //     printf("%d\n", *(int*)pair->data);
    //     LibLinkedList.insert(list, (void*)pair, -1);

    //     free(pair);
    // }

    // LibLinkedList.print(list, print_pair);
    
    // LibLinkedList.insert(list, (void*)pair, -1);
    // LibLinkedList.insert(list, (void*)pair, -1);
    // LibLinkedList.insert(list, (void*)pair, -1);
    // LibLinkedList.insert(list, (void*)pair, -1);
    // LibLinkedList.insert(list, (void*)pair, -1);
    // LibLinkedList.free(list, free_pair);
    
    return EXIT_SUCCESS;
}
