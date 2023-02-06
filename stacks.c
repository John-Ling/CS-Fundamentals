#include <stdio.h>
#include <string.h>

// implementation of the stack data type for learning purposes
#define MAX_SIZE 10

struct stack_t
{
    int values[MAX_SIZE]; // values within stack -1 represents a null value its represented by a / for some reason
    int stackPointer; // pointer to top value on stack
};
typedef struct stack_t stack;

void initialise_stack(stack *stack);
void push(stack *stack, int val);
void pop(stack *stack);
void peek(stack *stack);
void is_empty(stack *stack);
void is_full(stack *stack);
void display_stack(stack *stack);

int main(void)
{   
    stack myStack;
    myStack.stackPointer = -1;
    // example use of a stack
    stack* pointer = &myStack;
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
    return 0;
}

void initialise_stack(stack *stack)
{
    // this is not really necessary (you can use the stack as is)
    // but for learning purposes I want to visualise the null sections within the array
    // rather than leaving them as garbage values
    for (int i = 0; i < MAX_SIZE; i++)
        stack->values[i] = -1;
}

void push(stack *stack, int val)
{
    // adds element to the top of stack
    if (stack->stackPointer == MAX_SIZE - 1)
        printf("stack full!\n");
    else
    {
        printf("Pushing value: %i\n", val);
        stack->stackPointer++;
        stack->values[stack->stackPointer] = val;
    } 
}

void pop(stack *stack)
{
    // removes element from top of stack
    if (stack->stackPointer == -1)
        printf("stack empty!\n");
    else
    { 
        int ptr = stack->stackPointer;
        printf("Popping value: %i\n", stack->values[ptr]);
        stack->stackPointer--; 
    }
}
void peek(stack *stack)
{
    // returns a copy of the element on the top of the stack without removing it
    // returns -1 if stack is empty
    int ptr = stack->stackPointer;
    if (ptr == -1)
        printf("stack empty!\n");
    else 
        printf("%i is at the top of the stack\n", stack->values[ptr]);
}

void is_empty(stack *stack)
{
    // check if stack is empty
    if (stack->stackPointer == -1)
        printf("stack empty!\n");
    else 
        printf("Not empty!\n"); 
}

void is_full(stack *stack)
{
    if (stack->stackPointer == (MAX_SIZE - 1))
        printf("stack full!\n");
    else 
        printf("Not full!\n"); 
}

void display_stack(stack *stack)
{
    // display all values in stack including the stack pointer
    char pointerString[26] = " <-- stack pointer is here";
    char baseString[9];
    char outputString[30];
    char charInteger;
    
    for (int i = MAX_SIZE - 1; i > -1; i--)
    {
        strcpy(baseString, "Value: ");
        charInteger = stack->values[i] + '0';
        strncat(baseString, &charInteger, 1);
        strncat(outputString, baseString, strlen(baseString));
        if (stack->stackPointer == i) // add stack pointer label
            strncat(outputString, pointerString, strlen(pointerString));
        printf("%s\n", outputString);
        strcpy(outputString, "");
    }
}