#ifndef SkipList_H
#define SkipList_H

#include <stdlib.h>
#include "linked_lists.h"
#include "utils.h"


// try make below a fixed array for better cache locality
typedef struct SkipListNode_t {
    void* value;
    ListNode* next;
    struct SkipListNode_t* below;
} SkipListNode;

typedef struct SkipList_t {
    int layerCount; // keep a maximum of 16
    int nodeCount;  // number of nodes in the bottom layer
    SkipListNode* head; // head of skip list
    size_t dataSize;
} SkipList;

SkipList* sl_create(void* values[], size_t n, size_t dataSize);
void sl_insert(SkipList* skiplist, const void* value, )

#endif