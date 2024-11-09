#include <stdbool.h>
#include "linked_lists.h"

typedef struct Stack_t
{
    // no need for a stack pointer 
    // since the top of the stack will be the head of the linked list
    LinkedList* items; 
} Stack;

Stack* create_stack(int arr[], const int n);
int push(Stack *stack, const int val);
int pop(Stack *stack);
int peek(Stack *stack);
bool is_empty(Stack *stack);
int print_stack(Stack *stack);
int free_stack(Stack* stack);

struct LibStack_l {
    Stack* (*create_stack)(int arr[], const int n);
    int (*push)(Stack *stack, const int val);
    int (*pop)(Stack *stack);
    int (*peek)(Stack *stack);
    bool (*is_empty)(Stack *stack);
    int (*print_stack)(Stack *stack);
    int (*free_stack)(Stack* stack);
};

extern const struct LibStack_l LibStack;