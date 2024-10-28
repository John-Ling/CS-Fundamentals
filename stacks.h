#define MAX_SIZE 10

typedef struct 
{
    int values[MAX_SIZE]; // values within stack -1 represents a null value its represented by a / for some reason
    int stackPointer; // pointer to top value on Stack
} Stack;

int initialise_stack(Stack *stack);
int push(Stack *stack, const int val);
int pop(Stack *stack);
int peek(Stack *stack);
int is_empty(Stack *stack);
int is_full(Stack *stack);
int display_stack(Stack *stack);
