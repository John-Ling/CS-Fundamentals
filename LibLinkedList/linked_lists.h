#ifndef Linked_Lists_H
#define Linked_Lists_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode_t
{
    void* value;
    struct ListNode_t* next;
} ListNode;

typedef struct 
{
    int itemCount;
    ListNode* head; // front of list
    size_t dataSize; // size of elements stored
} LinkedList;

LinkedList* ll_create(void* values[], const size_t n, const size_t typeSize);
ListNode* _ll_create_node(void* data, const size_t size);
int _ll_insert_node(LinkedList* list, ListNode* node, const int index);
int ll_insert(LinkedList* list, void* value, const int index);
int ll_insert_int(LinkedList* list, int value, const int index);
int ll_insert_str(LinkedList* list, char* value, const int index);
int ll_insert_flt(LinkedList* list, float value, const int index);
int ll_insert_dbl(LinkedList* list, double value, const int index);
int ll_insert_chr(LinkedList* list, char value, const int index);
int ll_print(LinkedList* list, void print(const void*));
int ll_delete(LinkedList* list, const int index, void free_item(void*));
int ll_reverse(LinkedList* list);
int ll_search(LinkedList* list, void* search, int compare(const void*, const void*));
int ll_search_int(LinkedList* list, int search);
int ll_search_str(LinkedList* list, char* search);
int ll_search_chr(LinkedList* list, char search);
int ll_free(LinkedList* list, void free_item(void*));

struct LibLinkedList_l {
    // create an empty linked list by passing NULL
    // or convert any array into a linked list by converting it into void pointers
    // using array_to_void_array() and passing it
    // byte size (aka datatype) of items being stored needs to be specified
    LinkedList* (*create)(void* values[], const size_t n, const size_t typeSize);

    // inserts a value at index in a linked list
    // inserting at index -1 inserts at the end of the list
    int (*insert)(LinkedList* list, void* value, const int index);
    int (*insert_int)(LinkedList* list, int value, const int index);
    int (*insert_str)(LinkedList* list, char* value, const int index);
    int (*insert_flt)(LinkedList* list, float value, const int index);
    int (*insert_dbl)(LinkedList* list, double value, const int index);
    int (*insert_chr)(LinkedList* list, char value, const int index);

    
    int (*print)(LinkedList* list, void print(const void*));

    // remove a node using a user-defined free function at 
    // a 0-indexed position
    // deleting at index -1 deletes the node at the back
    int (*delete)(LinkedList* list, const int index, void free_item(void*));


    int (*reverse)(LinkedList* list);


    // check if a specific value in the linked list exists
    // matching is done by a user provided comparison function
    // return an integer referring to the 0-indexed position of the first matching value
    // returns -1 if unable to find
    int (*search)(LinkedList* list, void* search, int compare(const void*, const void*));
    int (*search_int)(LinkedList* list, int search);
    int (*search_str)(LinkedList* list, char* search);
    int (*search_chr)(LinkedList* list, char search);


    // performs free_item() on each item in the linked list
    // if free_item is NULL will default to basic free function
    int (*free)(LinkedList* list, void free_item(void*));
};

extern const struct LibLinkedList_l LibLinkedList;
#endif
