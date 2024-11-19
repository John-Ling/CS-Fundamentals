#ifndef Stack_H
#define Stacks_H    
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "linked_lists.h"

typedef struct Stack_t
{
    // no need for a stack pointer 
    // since the top of the stack will be the head of the linked list
    LinkedList* items; 
} Stack;

Stack* s_create(void* arr[], const size_t n, const size_t typeSize);
int s_push(Stack *stack, void* val);
int s_pop(Stack* stack, void* out);
int s_peek(Stack* stack, void* out);
bool s_empty(Stack *stack);
int s_print(Stack *stack, void (*print)(void* value));
int s_free(Stack* stack);

struct LibStack_l {
    Stack* (*create)(void* arr[], const size_t n, const size_t typeSize);
    int (*push)(Stack* stack, void* val);
    int (*pop)(Stack* stack, void* out);
    int (*peek)(Stack* stack, void* out);
    bool (*is_empty)(Stack* stack);
    int (*print)(Stack* stack, void (*print)(void* value));
    int (*free)(Stack* stack);
};

extern const struct LibStack_l LibStack;
#endif