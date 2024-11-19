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
    size_t dataSize;
} LinkedList;

LinkedList* ll_create(void* values[], const size_t n, const size_t typeSize);
int ll_insert(LinkedList* list, void* value, const int index);
int ll_insert_int(LinkedList* list, int value, const int index);
int ll_insert_str(LinkedList* list, char* value, const int index);
int ll_insert_flt(LinkedList* list, float value, const int index);
int ll_insert_dbl(LinkedList* list, double value, const int index);
int ll_insert_chr(LinkedList* list, char value, const int index);
int ll_print(LinkedList* list, void print(void*));
int ll_delete(LinkedList* list, const int index);
int ll_reverse(LinkedList* list);
int ll_free(LinkedList* list);

struct LibLinkedList_l {
    LinkedList* (*create)(void* values[], const size_t n, const size_t typeSize);
    int (*insert)(LinkedList* list, void* value, const int index);
    int (*insert_int)(LinkedList* list, int value, const int index);
    int (*insert_str)(LinkedList* list, char* value, const int index);
    int (*insert_flt)(LinkedList* list, float value, const int index);
    int (*insert_dbl)(LinkedList* list, double value, const int index);
    int (*insert_chr)(LinkedList* list, char value, const int index);
    int (*print)(LinkedList* list, void print(void*));
    int (*delete)(LinkedList* list, const int index);
    int (*reverse)(LinkedList* list);
    int (*free)(LinkedList* list);
};

extern const struct LibLinkedList_l LibLinkedList;
#endif