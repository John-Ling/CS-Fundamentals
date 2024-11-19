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
int s_push(Stack* stack, const void* value);
int s_push_int(Stack* stack, int value);
int s_push_str(Stack* stack, const char* value);
int s_push_dbl(Stack* stack, double value);
int s_push_flt(Stack* stack, float value);
int s_push_chr(Stack* stack, char value);
int s_pop(Stack* stack, void* out);
int s_peek(Stack* stack, void* out);
bool s_empty(Stack* stack);
int s_print(Stack* stack, void (*print)(const void* value));
int s_free(Stack* stack);

struct LibStack_l {
    Stack* (*create)(void* arr[], const size_t n, const size_t typeSize);
    int (*push)(Stack* stack, const void* value);
    int (*push_int)(Stack* stack, int value);
    int (*push_str)(Stack* stack, const char* value);
    int (*push_dbl)(Stack* stack, double value);
    int (*push_flt)(Stack* stack, float value);
    int (*push_chr)(Stack* stack, char value);
    int (*pop)(Stack* stack, void* out);
    int (*peek)(Stack* stack, void* out);
    bool (*is_empty)(Stack* stack);
    int (*print)(Stack* stack, void (*print)(const void* value));
    int (*free)(Stack* stack);
};

extern const struct LibStack_l LibStack;
#endif