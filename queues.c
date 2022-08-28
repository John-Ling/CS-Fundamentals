#include <stdio.h>
#include <string.h>

// implementation of the (circular) queue data type for educational purposes
#define MAX_SIZE 10

struct queue
{
    unsigned int values[MAX_SIZE];
    int frontPtr;
    int backPtr;
};
typedef struct queue Queue;

void enqueue(Queue *queue, int val);
void dequeue(Queue *queue);
void is_empty(Queue *queue);
void is_full(Queue *queue);
int _calculate_pointer(int ptr);
void intialise_queue(Queue *queue);
void display_queue(Queue *queue);

int main(void)
{
    Queue queue;
    queue.frontPtr = -1;
    queue.backPtr = -1;
    Queue* ptr = &queue;
    intialise_queue(ptr);
    
    //example use of a queue
    enqueue(ptr, 3);
    enqueue(ptr, 6);
    enqueue(ptr, 2);
    enqueue(ptr, 9);
    dequeue(ptr);
    dequeue(ptr);
    enqueue(ptr, 2);
    enqueue(ptr, 4);
    enqueue(ptr, 1);
    display_queue(ptr);
    enqueue(ptr, 6);
    enqueue(ptr, 6);
    enqueue(ptr, 6);
    enqueue(ptr, 8);
    display_queue(ptr);
    return 0;
}

int _calculate_pointer(int ptr)
{
    return (ptr + 1) % MAX_SIZE; // formula to move pointer foward and account for circular queue wrap around
}

void intialise_queue(Queue *queue)
{
    // this is not really necessary but I want to be able to visualise the null spaces within the queue
    // rather than  just seeing random garbage values
    // although the number is -1 since it's converted to a char using its ascii value 
    // it will be shown as a / because there are no ascii values for negative numbers
    for (int i = 0; i < MAX_SIZE; i++)
    {
        queue->values[i] = -1;
    }
}

void enqueue(Queue *queue, int val)
{
    // add an element to the queue
    int ptr = _calculate_pointer(queue->backPtr); 
    if (ptr == queue->frontPtr)
    {
        printf("Queue is full!\n");
    }
    else
    {
        printf("Enqueuing value: %i\n", val);
        queue->values[ptr] = val;
        queue->backPtr = ptr;
        if (queue->frontPtr == -1) // account for enqueing item when array is not completely filled
        {
            queue->frontPtr = 0; 
        }
    }
}

void dequeue(Queue *queue)
{
    // return an element from the front of the queue
    if (queue->frontPtr > queue->backPtr) 
    {
        printf("Queue is empty!\n");
    }
    else
    {
        int ptr = queue->frontPtr;
        int val = queue->values[ptr];
        queue->frontPtr = _calculate_pointer(queue->frontPtr);
        printf("Dequeuing value: %i\n", val);
    }
}

void is_empty(Queue *queue)
{
    if (_calculate_pointer(queue->frontPtr) > queue->backPtr)
    {
        printf("Queue is empty!\n");
    }
    else
    {
        printf("Queue is not empty\n");
    }
}

void is_full(Queue *queue)
{
    if (_calculate_pointer(queue->backPtr) == queue->frontPtr)
    {
        printf("Queue is full!\n");
    }
    else
    {
        printf("Queue is not full\n");
    }
}

void display_queue(Queue *queue)
{
    // show contents of queue including queue pointers and null values
    char frontPointerString[30] = " <-- Front pointer is here";
    char backPointerString[30] = " <-- Back pointer is here";
    char baseString[30];
    char outputString[90];
    char charInteger;

    for (int i = 0; i < MAX_SIZE; i++)
    {
        strcpy(baseString, "Value: ");
        charInteger = queue->values[i] + '0'; // convert integer to char using its ascii value
        strncat(baseString, &charInteger, 1);
        if (queue-> frontPtr == i)
        {
            strncat(baseString, frontPointerString, strlen(frontPointerString));
        }
        else if (queue->backPtr == i)
        {
            strncat(baseString, backPointerString, strlen(backPointerString));
        }
        printf("%s\n", baseString);
    }
}