#ifndef Linked_Lists_H
#define Linked_Lists_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct ListNode_t
{
    int value;
    struct ListNode_t* next;
} ListNode;

typedef struct LinkedList_t
{
    int itemCount;
    ListNode* head; // front of list
} LinkedList;

LinkedList* ll_create(int values[], const int n);
int ll_insert(LinkedList* list, const int value, const int index);
int ll_print(LinkedList* list);
int ll_delete(LinkedList* list, const int index);
int ll_reverse(LinkedList* list);
int ll_free(LinkedList* list);

struct LibLinkedList_l {
    LinkedList* (*create)(int values[], const int n);
    int (*insert)(LinkedList* list, const int value, const int index);
    int (*print)(LinkedList* list);
    int (*delete)(LinkedList* list, const int index);
    int (*reverse)(LinkedList* list);
    int (*free)(LinkedList* list);
};

extern const struct LibLinkedList_l LibLinkedList;
#endif