#include "queues.h"

// implementation of a standard queue data structure using a singly linked list for educational purposes

// create queue from array
Queue* q_create(int arr[], const int n)
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->items = LibLinkedList.create(arr, n);
    return queue;
}

int q_free(Queue* queue)
{
    LibLinkedList.free(queue->items);
    free(queue);
    queue = NULL;
    return EXIT_SUCCESS;
}

// add an element to the queue
int q_enqueue(Queue* queue, const int val)
{  
    // use linked list library to insert item to back
    return LibLinkedList.insert(queue->items, val, -1);
}

// return an element from the front of the queue
// pass null to out if you don't need to receive the item
int q_dequeue(Queue* queue, int* out)
{
    if (q_empty(queue))
    {
        return EXIT_FAILURE;
    }

    if (out != NULL)
    {
        *out = queue->items->head->value;
    }

    // delete element at head
    return LibLinkedList.delete(queue->items, 0);
}

int q_peek(Queue* queue, int* out)
{
    if (q_empty(queue) || out == NULL)
    {
        EXIT_FAILURE;
    }

    *out = queue->items->head->value;
    return EXIT_SUCCESS;
}

bool q_empty(Queue* queue)
{
    return queue->items == NULL || queue->items->head == NULL;    
}

int q_print(Queue* queue)
{
    return LibLinkedList.print(queue->items);
}

const struct LibQueue_l LibQueue = {
    .create = q_create,
    .enqueue = q_enqueue,
    .print = q_print,
    .dequeue = q_dequeue,
    .peek = q_peek,
    .empty = q_empty,
    .free = q_free
};