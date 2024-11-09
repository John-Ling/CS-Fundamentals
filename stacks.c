#include <stdlib.h>
#include "stacks.h"

// implementation of the stack data type for learning purposes

Stack* create_stack(int arr[], const int n)
{
    if (arr == NULL && n != 0)
    {
        return NULL;
    }

    Stack* stack = (Stack*)malloc(sizeof(Stack));

    // to create a stack we'll insert elements only at the head
    // therefore we can't use the create_list function
    // which inserts elements to the back
    stack->items = (LinkedList*)malloc(sizeof(LinkedList));
    
    for (int i = 0; i < n; i++)
    {
        // insert at the head of the linked list
        LibLinkedList.insert(stack->items, arr[i], 0);
    }
    return stack;
}

int free_stack(Stack* stack)
{
    LibLinkedList.free_list(stack->items);
    free(stack);
    stack = NULL;
    return EXIT_SUCCESS;
}

// pushes an item onto the stack
int push(Stack *stack, const int val)
{
    LibLinkedList.insert(stack->items, val, 0);
    return EXIT_SUCCESS;
}

// pop a value off the stack
int pop(Stack* stack)
{
    LibLinkedList.delete(stack->items, 0);
    return EXIT_SUCCESS;
}

// returns a copy of the element on the top of the stack without removing it
// returns -1 if stack is empty
int peek(Stack* stack)
{    
    if (stack->items == NULL)
    {
        // empty stack
        return -1;
    }

    return stack->items->head->value;
}

// check if stack is empty
bool is_empty(Stack *stack)
{
    return stack->items == NULL;
}

int print_stack(Stack *stack)
{
    LibLinkedList.print_list(stack->items);
    return EXIT_SUCCESS;
}

const struct LibStack_l LibStack = {
    .create_stack = create_stack,
    .push = push,
    .print_stack = print_stack,
    .pop = pop,
    .peek = peek,
    .is_empty = is_empty,
    .free_stack = free_stack
};