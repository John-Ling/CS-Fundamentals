#define MAX_SIZE 10

typedef struct
{
    unsigned int values[MAX_SIZE];
    int frontPointer;
    int backPointer;
} Queue;

int enqueue(Queue *queue, const int val);
int dequeue(Queue *queue);
int is_empty(Queue *queue);
int is_full(Queue *queue);
static int calculate_pointer(const int pointer);
int intialise_queue(Queue *queue);
int display_queue(Queue *queue);
