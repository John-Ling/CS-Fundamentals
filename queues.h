#include <stdbool.h>
#include "linked_lists.h"

typedef struct Queue_t
{
    LinkedList* items;
} Queue;

int enqueue(Queue* queue, const int val);
int dequeue(Queue* queue);
bool is_empty(Queue* queue);
int is_full(Queue* queue);
int display_queue(Queue* queue);
