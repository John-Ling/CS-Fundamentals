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

Stack* s_create(int arr[], const int n);
int s_push(Stack *stack, const int val);
int s_pop(Stack* stack, int* out);
int s_peek(Stack* stack, int* out);
bool s_empty(Stack *stack);
int s_print(Stack *stack);
int s_free(Stack* stack);

struct LibStack_l {
    Stack* (*create)(int arr[], const int n);
    int (*push)(Stack* stack, const int val);
    int (*pop)(Stack* stack, int* out);
    int (*peek)(Stack* stack, int* out);
    bool (*empty)(Stack* stack);
    int (*print)(Stack* stack);
    int (*free)(Stack* stack);
};

extern const struct LibStack_l LibStack;
#endif