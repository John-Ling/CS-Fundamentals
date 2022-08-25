#include <stdio.h>
#include <string.h>

// implementation of the stack data type for learning purposes
#define MAX_SIZE 10

struct stack
{
    int values[MAX_SIZE]; // values within stack -1 represents a null value its represented by a / for some reason
    int stackPtr; // pointer to top value on stack
};
typedef struct stack Stack;

void intialise_stack(Stack *stack);
void push(Stack *stack, int val);
void pop(Stack *stack);
void peek(Stack *stack);
void is_empty(Stack *stack);
void is_full(Stack *stack);
void display_stack(Stack *stack);

int main(void)
{   
    Stack stack;
    stack.stackPtr = -1;
    intialise_stack(&stack); // for learning purposes run this
    for (int i = 0; i < MAX_SIZE; i++)
    {
        printf("%i\n", stack.values[i]);
    }
    // example use of a stack
    Stack* pointer = &stack;
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
    return 0;
}

void intialise_stack(Stack *stack)
{
    // this is not really necessary (you can use the stack as is)
    // but for learning purposes I want to visualise the null sections within the array
    // rather than leaving them as garbage values
    for (int i = 0; i < MAX_SIZE; i++)
    {
        stack->values[i] = -1;
    }
}

void push(Stack *stack, int val)
{
    // adds element to the top of stack
    if (stack->stackPtr == MAX_SIZE - 1)
    {
        printf("Stack full!\n");
    }
    else
    {
        printf("Pushing value: %i\n", val);
        stack->stackPtr++;
        stack->values[stack->stackPtr] = val;
    } 
}

void pop(Stack *stack)
{
    // removes element from top of stack
    if (stack->stackPtr == -1)
    {
        printf("Stack empty!\n");
    } 
    else
    { 
        int ptr = stack->stackPtr;
        printf("Popping value: %i\n", stack->values[ptr]);
        stack->stackPtr--; 
    }
}
void peek(Stack *stack)
{
    // returns a copy of the element on the top of the stack without removing it
    // returns -1 if stack is empty
    int ptr = stack->stackPtr;
    if (ptr == -1)
    {
        printf("Stack empty!\n");
    }
    else 
    {
        printf("%i is at the top of the stack\n", stack->values[ptr]);
    }
}

void is_empty(Stack *stack)
{
    // check if stack is empty
    if (stack->stackPtr == -1)
    {
        printf("Stack empty!\n");
    }
    else 
    { 
        printf("Not empty!\n"); 
    }
}

void is_full(Stack *stack)
{
    if (stack->stackPtr == (MAX_SIZE - 1))
    {
        printf("Stack full!\n");
    }
    else 
    { 
        printf("Not full!\n"); 
    }
}

void display_stack(Stack *stack)
{
    // display all values in stack including the stack pointer
    char pointerString[30] = " <-- Stack pointer is here";
    char baseString[30];
    char outputString[60];
    char charInteger;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        strcpy(baseString, "Value: ");
        charInteger = stack->values[i] + '0';
        strncat(baseString, &charInteger, 1);
        strncat(outputString, baseString, strlen(baseString));
        if (stack->stackPtr == i)
        {
            strncat(outputString, pointerString, strlen(pointerString));
        }
        printf("%s\n", outputString);
        strcpy(outputString, "");
    }
}