#include <stdio.h>
#include <string.h>

// implementation of the (circular) queue data type for educational purposes
#define MAX_SIZE 10

struct queue_t
{
    unsigned int values[MAX_SIZE];
    int frontPointer;
    int backPointer;
};
typedef struct queue_t queue;

void enqueue(queue *queue, int val);
void dequeue(queue *queue);
void is_empty(queue *queue);
void is_full(queue *queue);
int _calculate_pointer(int pointer);
void intialise_queue(queue *queue);
void display_queue(queue *queue);

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
    return (pointer + 1) % MAX_SIZE; // formula to move pointer foward and account for circular queue wrap around
}

void intialise_queue(queue *queue)
{
    // this is not really necessary but I want to be able to visualise the null spaces within the queue
    // rather than  just seeing random garbage values
    // although the number is -1 since it's converted to a char using its ascii value 
    // it will be shown as a / because there are no ascii values for negative numbers
    for (int i = 0; i < MAX_SIZE; i++)
        queue->values[i] = -1;
}

void enqueue(queue *queue, int val)
{
    // add an element to the queue
    int pointer = _calculate_pointer(queue->backPointer); 
    if (pointer == queue->frontPointer)
        printf("queue is full!\n");
    else
    {
        printf("Enqueuing value: %i\n", val);
        queue->values[pointer] = val;
        queue->backPointer = pointer;
        if (queue->frontPointer == -1) // account for enqueing item when array is not completely filled
            queue->frontPointer = 0; 
    }
}

void dequeue(queue *queue)
{
    // return an element from the front of the queue
    if (queue->frontPointer == -1 && queue->backPointer == -1) 
        printf("queue is empty!\n");
    else
    {
        int pointer = queue->frontPointer;
        int val = queue->values[pointer];
        queue->frontPointer = _calculate_pointer(queue->frontPointer);
        printf("Dequeuing value: %i\n", val);
    }
}

void is_empty(queue *queue)
{
    if (_calculate_pointer(queue->frontPointer) > queue->backPointer)
        printf("queue is empty!\n");
    else
        printf("queue is not empty\n");
}

void is_full(queue *queue)
{
    if (_calculate_pointer(queue->backPointer) == queue->frontPointer)
        printf("queue is full!\n");
    else
        printf("queue is not full\n");
}

void display_queue(queue *queue)
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
        charInteger = queue->values[i] + '0'; // convert integer to char using its ascii value
        strncat(baseString, &charInteger, 1);
        if (queue-> frontPointer == i)
            strncat(baseString, frontPointerString, strlen(frontPointerString));
        else if (queue->backPointer == i)
            strncat(baseString, backPointerString, strlen(backPointerString));
        printf("%s\n", baseString);
    }
}