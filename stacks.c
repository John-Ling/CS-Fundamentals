#include "stacks.h"

// implementation of the stack data structure using a singly linked list for learning purposes

// create stack out of array
Stack* s_create(int arr[], const int n)
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

int s_free(Stack* stack)
{
    LibLinkedList.free(stack->items);
    free(stack);
    stack = NULL;
    return EXIT_SUCCESS;
}

// pushes an item onto the stack
int s_push(Stack *stack, const int val)
{
    LibLinkedList.insert(stack->items, val, 0);
    return EXIT_SUCCESS;
}

// pop a value off the stack
// pass null to out if you don't need to receive the item
int s_pop(Stack* stack, int* out)
{
    if (s_empty(stack))
    {
        return EXIT_FAILURE;
    }

    if (out != NULL)
    {
        *out = stack->items->head->value;
    }
    return LibLinkedList.delete(stack->items, 0);
}

int s_peek(Stack* stack, int* out)
{
    if (s_empty(stack) || out == NULL)
    {
        EXIT_FAILURE;
    }

    *out = stack->items->head->value;
    return EXIT_SUCCESS;
}

bool s_empty(Stack *stack)
{
    return stack->items == NULL || stack->items->head == NULL;
}

int s_print(Stack *stack)
{
    LibLinkedList.print(stack->items);
    return EXIT_SUCCESS;
}

const struct LibStack_l LibStack = {
    .create = s_create,
    .push = s_push,
    .print = s_print,
    .peek = s_peek,
    .pop = s_pop,
    .empty = s_empty,
    .free = s_free
};