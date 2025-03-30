#ifndef Linked_Lists_H
#define Linked_Lists_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

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
int ll_insert(LinkedList* list, void* value, const int index);
int ll_insert_int(LinkedList* list, int value, const int index);
int ll_insert_str(LinkedList* list, char* value, const int index);
int ll_insert_flt(LinkedList* list, float value, const int index);
int ll_insert_dbl(LinkedList* list, double value, const int index);
int ll_insert_chr(LinkedList* list, char value, const int index);
int ll_print(LinkedList* list, void print(const void*));
int ll_delete(LinkedList* list, const int index);
int ll_reverse(LinkedList* list);
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
    int (*delete)(LinkedList* list, const int index);
    int (*reverse)(LinkedList* list);
    
    // performs free_item() on each item in the linked list
    // if free_item is NULL will default to basic free function
    int (*free)(LinkedList* list, void free_item(void*));
};

extern const struct LibLinkedList_l LibLinkedList;
#endif