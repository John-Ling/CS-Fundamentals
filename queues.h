#ifndef Queues_H
#define Queues_H
#include <stdbool.h>
#include <stdlib.h>
#include "linked_lists.h"


typedef struct Queue_t
{
    LinkedList* items;
} Queue;

Queue* q_create(int arr[], const int n);
int q_free(Queue* queue);
int q_enqueue(Queue* queue, const int val);
int q_dequeue(Queue* queue, int* out);
int q_peek(Queue* queue, int* out);
bool q_empty(Queue* queue);
int q_print(Queue* queue);

struct LibQueue_l {
    Queue* (*create)(int arr[], const int n);
    int (*enqueue)(Queue* queue, const int val);
    int (*dequeue)(Queue* queue, int* out);
    int (*peek)(Queue* queue, int* out);
    bool (*empty)(Queue* queue);
    int (*free)(Queue* queue);
    int (*print)(Queue* queue);
};

extern const struct LibQueue_l LibQueue;
#endif