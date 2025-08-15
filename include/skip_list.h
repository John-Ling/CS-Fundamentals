#ifndef SkipList_H
#define SkipList_H

#include <stdlib.h>
#include <time.h>
#include "linked_lists.h"
#include "utils.h"

#define DEBUG 1

#define _MAX_SKIP_LIST_LAYERS 16

typedef struct SkipListNode_t {
    void* value;
    struct SkipListNode_t* below;
    int layerNumber; 
} SkipListNode;

typedef struct SkipList_t {
    int layerCount; // keep a maximum of 16
    LinkedList* layers[_MAX_SKIP_LIST_LAYERS]; 
    size_t dataSize;
} SkipList;

SkipList* sl_create(void* values[], size_t n, size_t dataSize);
int sl_insert(SkipList* list, const void* value, int compare(const void*, const void*));
int sl_insert_int(SkipList* list, int value);

int sl_delete(SkipList* list, int index, void free_item(const void*));

int sl_print(SkipList* list, void print(const void*));

int sl_search(SkipList* list, const void* value, int compare(const void*, const void*));

int sl_free(SkipList* list, void free_item(const void*));

#endif