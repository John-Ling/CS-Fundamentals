#ifndef Queues_H
#define Queues_H
#include <stdbool.h>
#include <stdlib.h>
#include "linked_lists.h"


typedef struct Queue_t
{
    LinkedList* items;
} Queue;

Queue* create_queue(int arr[], const int n);
int free_queue(Queue* queue);
int enqueue(Queue* queue, const int val);
int dequeue(Queue* queue, int* out);
int queue_peek(Queue* queue, int* out);
bool queue_empty(Queue* queue);
int print_queue(Queue* queue);

struct LibQueue_l {
    Queue* (*create_queue)(int arr[], const int n);
    int (*enqueue)(Queue* queue, const int val);
    int (*dequeue)(Queue* queue, int* out);
    int (*queue_peek)(Queue* queue, int* out);
    bool (*queue_empty)(Queue* queue);
    int (*free_queue)(Queue* queue);
    int (*print_queue)(Queue* queue);
};

extern const struct LibQueue_l LibQueue;
#endif