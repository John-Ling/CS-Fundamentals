#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queues.h"

// implementation of the (circular) queue data type for educational purposes

int main(void)
{
    queue myQueue;
    myQueue.frontPointer = -1;
    myQueue.backPointer = -1;
    queue* pointer = &myQueue;
    intialise_queue(pointer);
    
    //example use of a queue
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
    return 0;
}

int _calculate_pointer(int pointer)
{
    // formula to move pointer foward and account for circular queue wrap around
    return (pointer + 1) % MAX_SIZE; 
}

int intialise_queue(queue *queue)
{
    // this is not really necessary but 
    // I want to be able to visualise the null spaces within the queue
    // rather than  just seeing random garbage values
    // although the number is -1 since it's converted to a char using its ascii value 
    // it will be shown as a / because there are no ascii values for negative numbers
    for (int i = 0; i < MAX_SIZE; i++)
    {
        queue->values[i] = -1;
    }
    return 0;   
}

int enqueue(queue *queue, int val)
{
    // add an element to the queue
    int pointer = _calculate_pointer(queue->backPointer); 
    if (pointer == queue->frontPointer)
    {
        printf("queue is full!\n");
        return 1;
    }

    printf("Enqueuing value: %i\n", val);
    queue->values[pointer] = val;
    queue->backPointer = pointer;
    // account for enqueing item when array is not completely filled
    if (queue->frontPointer == -1) 
    {
        queue->frontPointer = 0; 
    }

    return 0;
}

int dequeue(queue *queue)
{
    // return an element from the front of the queue
    if (queue->frontPointer == -1 && queue->backPointer == -1) 
    {
        printf("queue is empty!\n");
        return 1;
    }
    else
    {
        int pointer = queue->frontPointer;
        int val = queue->values[pointer];
        queue->frontPointer = _calculate_pointer(queue->frontPointer);
        printf("Dequeuing value: %i\n", val);
    }
    return 0;
}

int is_empty(queue *queue)
{
    if (_calculate_pointer(queue->frontPointer) > queue->backPointer)
    {
        printf("queue is empty!\n");
        return 1;
    }
    printf("queue is not empty\n");
    return 0;
}

int is_full(queue *queue)
{
    if (_calculate_pointer(queue->backPointer) == queue->frontPointer)
    {
        printf("queue is full!\n");
        return 1;
    }
    printf("queue is not full\n");
    return 0;
}

int display_queue(queue *queue)
{
    // show contents of queue including queue pointers and null values
    char frontPointerString[35] = " <-- Front pointer is here";
    char backPointerString[35] = " <-- Back pointer is here";
    char baseString[35];
    char outputString[95];
    char charInteger;

    for (int i = 0; i < MAX_SIZE; i++)
    {
        strcpy(baseString, "Value: ");
        // convert integer to char using its ascii value
        charInteger = queue->values[i] + '0'; 
        strncat(baseString, &charInteger, 1);
        if (queue-> frontPointer == i)
        {
            strncat(baseString, frontPointerString, strlen(frontPointerString));
        }
        else if (queue->backPointer == i)
        {
            strncat(baseString, backPointerString, strlen(backPointerString));
        }
        printf("%s\n", baseString);
    }

    return 0;
}