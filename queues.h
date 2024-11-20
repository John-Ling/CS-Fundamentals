#ifndef Queues_H
#define Queues_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "linked_lists.h"

typedef struct
{
    LinkedList* items;
} Queue;

Queue* q_create(void* arr[], const size_t n, const size_t typeSize);
int q_free(Queue* queue, void (*free_item)(void*));
int q_enqueue(Queue* queue, const void* value);
int q_enqueue_int(Queue* queue, int value);
int q_enqueue_str(Queue* queue, const char* value);
int q_enqueue_flt(Queue* queue, float value);
int q_enqueue_dbl(Queue* queue, double value);
int q_enqueue_chr(Queue* queue, char value);
int q_dequeue(Queue* queue, void* out);
int q_peek(Queue* queue, void* out);
bool q_empty(Queue* queue);
int q_print(Queue* queue, void (*print)(const void*));

struct LibQueue_l {
    Queue* (*create)(void* arr[], const size_t n, const size_t typeSize);
    int (*enqueue)(Queue* queue, const void* value);
    int (*enqueue_int)(Queue* queue, int value);
    int (*enqueue_str)(Queue* queue, const char* value);
    int (*enqueue_flt)(Queue* queue, float value);
    int (*enqueue_dbl)(Queue* queue, double value);
    int (*enqueue_chr)(Queue* queue, char value);
    int (*dequeue)(Queue* queue, void* out);
    int (*peek)(Queue* queue, void* out);
    bool (*is_empty)(Queue* queue);
    int (*free)(Queue* queue, void (*print)(void*));
    int (*print)(Queue* queue, void (*print)(const void*));
};

extern const struct LibQueue_l LibQueue;
#endif