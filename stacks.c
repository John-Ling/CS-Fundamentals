#include <stdio.h>
#include <stdlib.h>

#include "stacks.h"

// implementation of the stack data type for learning purposes

int main(void)
{   
    Stack myStack;
    myStack.stackPointer = -1;
    // example use of a stack
    Stack* pointer = &myStack;
    initialise_stack(&myStack); // for learning purposes run this
    display_stack(pointer);
    push(pointer, 1);
    push(pointer, 2);
    push(pointer, 3);
    push(pointer, 4);
    peek(pointer);
    push(pointer, 6);
    push(pointer, 9);
    pop(pointer);
    display_stack(pointer);
    push(pointer, 1);
    push(pointer, 5);
    push(pointer, 2);
    display_stack(pointer);
    return EXIT_SUCCESS;
}

int initialise_stack(Stack *stack)
{
    // this is not really necessary (you can use the stack as is)
    // but for learning purposes I want to visualise the null sections within the array
    // rather than leaving them as garbage values
    for (int i = 0; i < MAX_SIZE; i++)
    {
        stack->values[i] = -1;
    }
    return EXIT_SUCCESS; 
}

int push(Stack *stack, const int val)
{
    // adds element to the top of Stack
    if (stack->stackPointer == MAX_SIZE - 1)
    {
        printf("Stack full!\n");
        return EXIT_FAILURE;
    }
    else
    {
        printf("Pushing value: %i\n", val);
        stack->stackPointer++;
        stack->values[stack->stackPointer] = val;
    } 
    return EXIT_SUCCESS;
}

int pop(Stack *stack)
{
    // removes element from top of stack
    if (stack->stackPointer == -1)
    {
        printf("Stack empty!\n");
        return EXIT_FAILURE;
    }
    else
    { 
        int ptr = stack->stackPointer;
        printf("Popping value: %i\n", stack->values[ptr]);
        stack->stackPointer--; 
    }
    return EXIT_SUCCESS;
}

int peek(Stack *stack)
{
    // returns a copy of the element on the top of the stack without removing it
    // returns -1 if stack is empty
    int ptr = stack->stackPointer;
    if (ptr == -1)
    {
        printf("Stack empty!\n");
        return EXIT_FAILURE;
    }
    else 
    {
        printf("%i is at the top of the Stack\n", stack->values[ptr]);
    }
    return EXIT_SUCCESS;
}

int is_empty(Stack *stack)
{
    // check if stack is empty
    if (stack->stackPointer == -1)
    {
        printf("Stack empty!\n");
        return EXIT_FAILURE;
    }
    else 
    {
        printf("Not empty!\n"); 
    }
    return EXIT_SUCCESS;
}

int is_full(Stack *stack)
{
    if (stack->stackPointer == (MAX_SIZE - 1))
    {
        printf("Stack full!\n");
        return EXIT_FAILURE;
    }
    else 
    {
        printf("Not full!\n"); 
    }
    return EXIT_SUCCESS;
}

int display_stack(Stack *stack)
{
    // display all values in stack including the stack pointer
    for (int i = MAX_SIZE - 1; i > -1; i--)
    {
        printf("Value: %d", stack->values[i]);
        if (stack->stackPointer == i)
        {
            printf("<-- Stack pointer is here");
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}