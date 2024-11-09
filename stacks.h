#ifndef Stack_H
#define Stacks_H    
#include <stdbool.h>
#include <stdlib.h>
#include "linked_lists.h"

typedef struct Stack_t
{
    // no need for a stack pointer 
    // since the top of the stack will be the head of the linked list
    LinkedList* items; 
} Stack;

Stack* create_stack(int arr[], const int n);
int push(Stack *stack, const int val);
int pop(Stack* stack, int* out);
int peek(Stack* stack, int* out);
bool stack_empty(Stack *stack);
int print_stack(Stack *stack);
int free_stack(Stack* stack);

struct LibStack_l {
    Stack* (*create_stack)(int arr[], const int n);
    int (*push)(Stack* stack, const int val);
    int (*pop)(Stack* stack, int* out);
    int (*peek)(Stack* stack, int* out);
    bool (*stack_empty)(Stack* stack);
    int (*print_stack)(Stack* stack);
    int (*free_stack)(Stack* stack);
};

extern const struct LibStack_l LibStack;
#endif