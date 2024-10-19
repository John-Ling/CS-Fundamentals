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
