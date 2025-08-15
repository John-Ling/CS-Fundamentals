#include "queues.h"

// implementation of a standard queue data structure using a singly linked list for educational purposes

// create queue from array
Queue* q_create(void* arr[], const size_t n, const size_t typeSize)
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->items = LibLinkedList.create(arr, n, typeSize);
    return queue;
}

int q_free(Queue* queue, void (*free_item)(void*))
{
    LibLinkedList.free(queue->items, free_item);
    free(queue);
    queue = NULL;
    return EXIT_SUCCESS;
}

// add an element to the queue
int q_enqueue(Queue* queue, const void* value)
{  
    // use linked list library to insert item to back
    return LibLinkedList.insert(queue->items, value, -1);
}

int q_enqueue_int(Queue* queue, int value)
{
    return q_enqueue(queue, &value);
}

int q_enqueue_str(Queue* queue, const char* value)
{
    return q_enqueue(queue, (void*)value);
}

int q_enqueue_flt(Queue* queue, float value)
{
    return q_enqueue(queue, &value);
}

int q_enqueue_dbl(Queue* queue, double value)
{
    return q_enqueue(queue, &value);
}

int q_enqueue_chr(Queue* queue, char value)
{
    return q_enqueue(queue, &value);
}

// return an element from the front of the queue
// pass null to out if you don't need to receive the item
int q_dequeue(Queue* queue, void* out)
{
    if (q_empty(queue))
    {
        return EXIT_FAILURE;
    }

    if (out != NULL)
    {
        memcpy(out, queue->items->head->value, queue->items->dataSize);
    }

    // delete element at head
    return LibLinkedList.delete(queue->items, 0);
}

int q_peek(Queue* queue, void* out)
{
    if (q_empty(queue) || out == NULL)
    {
        EXIT_FAILURE;
    }

    memcpy(out, queue->items->head->value, queue->items->dataSize);
    return EXIT_SUCCESS;
}

bool q_empty(Queue* queue)
{
    return queue->items == NULL || queue->items->head == NULL;    
}

int q_print(Queue* queue, void (*print)(const void*))
{
    return LibLinkedList.print(queue->items, print);
}

const struct LibQueue_l LibQueue = {
    .create = q_create,
    .enqueue = q_enqueue,
    .enqueue_int = q_enqueue_int,
    .enqueue_str = q_enqueue_str,
    .enqueue_chr = q_enqueue_chr,
    .enqueue_dbl = q_enqueue_dbl,
    .enqueue_flt = q_enqueue_flt,
    .print = q_print,
    .dequeue = q_dequeue,
    .peek = q_peek,
    .is_empty = q_empty,
    .free = q_free
};