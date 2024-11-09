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

LinkedList* create_list(int values[], const int n);
int insert(LinkedList* list, const int value, const int index);
int print_list(LinkedList* list);
int delete(LinkedList* list, const int index);
int reverse(LinkedList* list);
int free_list(LinkedList* list);

struct LibLinkedList_l {
    LinkedList* (*create_list)(int values[], const int n);
    int (*insert)(LinkedList* list, const int value, const int index);
    int (*print_list)(LinkedList* list);
    int (*delete)(LinkedList* list, const int index);
    int (*reverse)(LinkedList* list);
    int (*free_list)(LinkedList* list);
};

extern const struct LibLinkedList_l LibLinkedList;
#endif