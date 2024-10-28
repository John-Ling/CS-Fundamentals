#include <stdio.h>
#include <stdlib.h>

#include "queues.h"

// implementation of a circular queue data for educational purposes

int main(void)
{
    Queue myQueue;
    myQueue.frontPointer = -1;
    myQueue.backPointer = -1;
    Queue* pointer = &myQueue;
    intialise_queue(pointer);
    
    //example use of a Queue
    enqueue(pointer, 3);
    enqueue(pointer, 6);
    enqueue(pointer, 2);
    enqueue(pointer, 9);
    dequeue(pointer);
    dequeue(pointer);
    enqueue(pointer, 2);
    enqueue(pointer, 4);
    enqueue(pointer, 1);
    display_queue(pointer);
    enqueue(pointer, 6);
    enqueue(pointer, 6);
    display_queue(pointer);
    dequeue(pointer);
    enqueue(pointer, 0);
    enqueue(pointer, 0);
    enqueue(pointer, 0);
    enqueue(pointer, 0);
    enqueue(pointer, 0);
    display_queue(pointer);
    dequeue(pointer);
    display_queue(pointer);
    enqueue(pointer, 3);
    display_queue(pointer);
    return EXIT_SUCCESS;
}

static int calculate_pointer(const int pointer)
{
    // formula to move pointer foward and account for circular Queue wrap around
    return (pointer + 1) % MAX_SIZE; 
}

int intialise_queue(Queue *queue)
{
    // this is not really necessary but 
    // I want to be able to visualise the null spaces within the Queue
    // rather than  just seeing random garbage values
    // although the number is -1 since it's converted to a char using its ascii value 
    // it will be shown as a / because there are no ascii values for negative numbers
    for (int i = 0; i < MAX_SIZE; i++)
    {
        queue->values[i] = -1;
    }
    return EXIT_SUCCESS;   
}

int enqueue(Queue *queue, const int val)
{
    // add an element to the Queue
    int pointer = calculate_pointer(queue->backPointer); 
    if (pointer == queue->frontPointer)
    {
        printf("Queue is full!\n");
        return EXIT_FAILURE;
    }

    printf("Enqueuing value: %i\n", val);
    queue->values[pointer] = val;
    queue->backPointer = pointer;
    // account for enqueing item when array is not completely filled
    if (queue->frontPointer == -1) 
    {
        queue->frontPointer = 0; 
    }

    return EXIT_SUCCESS;
}

int dequeue(Queue *queue)
{
    // return an element from the front of the queue
    if (queue->frontPointer == -1 && queue->backPointer == -1) 
    {
        printf("Queue is empty!\n");
        return EXIT_FAILURE;
    }
    else
    {
        int pointer = queue->frontPointer;
        int val = queue->values[pointer];
        queue->frontPointer = calculate_pointer(queue->frontPointer);
        printf("Dequeuing value: %i\n", val);
    }
    return EXIT_SUCCESS;
}

int is_empty(Queue *queue)
{
    if (calculate_pointer(queue->frontPointer) > queue->backPointer)
    {
        printf("Queue is empty!\n");
        return EXIT_FAILURE;
    }
    printf("Queue is not empty\n");
    return EXIT_SUCCESS;
}

int is_full(Queue *queue)
{
    if (calculate_pointer(queue->backPointer) == queue->frontPointer)
    {
        printf("Queue is full!\n");
        return EXIT_FAILURE;
    }
    printf("Queue is not full\n");
    return EXIT_SUCCESS;
}

int display_queue(Queue *queue)
{
    // show contents of Queue including Queue pointers and null values
    for (int i = 0; i < MAX_SIZE; i++)
    {
        printf("Value: %d ", queue->values[i]);
        if (queue->frontPointer == i)
        {
            printf("<-- Front pointer is here");
        }
        else if (queue->backPointer == i)
        {
            printf("<-- Back pointer is here");
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}