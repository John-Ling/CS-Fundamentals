#include <stdio.h>
#include <stdlib.h>

#include "queues.h"

// implementation of a standard queue data structure using a singly linked list for educational purposes

// create queue out of array
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
// returns null if queue is empty or function fails
int dequeue(Queue* queue)
{
    if (queue->items == NULL)
    {
        // empty queue
        return NULL;        
    }

    // get element
    int val = queue->items->head->value;

    // delete element at head
    if (LibLinkedList.delete(queue->items, 0)  == EXIT_FAILURE)
    {
        return NULL;
    }
    return val;
}

// get item at front of queue'
// returns NULL if empty
int peek(Queue* queue)
{
    if (is_empty(queue))
    {
        return NULL;
    }
    return queue->items->head->value;
}

bool is_empty(Queue* queue)
{
    return queue->items == NULL || queue->items->head == NULL;    
}

int display_queue(Queue* queue)
{
    return LibLinkedList.print_list(queue->items);
}