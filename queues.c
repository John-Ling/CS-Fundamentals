#include "queues.h"

// implementation of a standard queue data structure using a singly linked list for educational purposes

// create queue from array
Queue* create_queue(int arr[], const int n)
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->items = LibLinkedList.create_list(arr, n);
    return queue;
}

int free_queue(Queue* queue)
{
    LibLinkedList.free_list(queue->items);
    free(queue);
    queue = NULL;
    return EXIT_SUCCESS;
}

// add an element to the queue
int enqueue(Queue* queue, const int val)
{  
    // use linked list library to insert item to back
    return LibLinkedList.insert(queue->items, val, -1);
}

// return an element from the front of the queue
// pass null to out if you don't need to receive the item
int dequeue(Queue* queue, int* out)
{
    if (queue_empty(queue))
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


int queue_peek(Queue* queue, int* out)
{
    if (queue_empty(queue) || out == NULL)
    {
        EXIT_FAILURE;
    }

    *out = queue->items->head->value;
    return EXIT_SUCCESS;
}

bool queue_empty(Queue* queue)
{
    return queue->items == NULL || queue->items->head == NULL;    
}

int print_queue(Queue* queue)
{
    return LibLinkedList.print_list(queue->items);
}

const struct LibQueue_l LibQueue = {
    .create_queue = create_queue,
    .enqueue = enqueue,
    .print_queue = print_queue,
    .dequeue = dequeue,
    .queue_peek = queue_peek,
    .queue_empty = queue_empty,
    .free_queue = free_queue
};