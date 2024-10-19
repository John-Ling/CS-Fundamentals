#define MAX_SIZE 10

struct queue_t
{
    unsigned int values[MAX_SIZE];
    int frontPointer;
    int backPointer;
};
typedef struct queue_t queue;

int enqueue(queue *queue, int val);
int dequeue(queue *queue);
int is_empty(queue *queue);
int is_full(queue *queue);
int _calculate_pointer(int pointer);
int intialise_queue(queue *queue);
int display_queue(queue *queue);
