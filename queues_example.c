#include <stdio.h>
#include <stdlib.h>

#include "queues.h"
#include "include/utils.h"

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf("Pass values to form the array\n");
        return EXIT_FAILURE;
    }
    const int n = argc - 1;

    int arr[n];
    for (int i = 1; i < argc; i++)
    {
        arr[i - 1] = atoi(argv[i]);
    }
    Queue* queue = LibQueue.create(CONVERT_ARRAY(arr, n), n, sizeof(int));

    LibQueue.print(queue, print_int);

    LibQueue.dequeue(queue, NULL);
    LibQueue.dequeue(queue, NULL);
    LibQueue.dequeue(queue, NULL);
    LibQueue.dequeue(queue, NULL);
    LibQueue.dequeue(queue, NULL);
    LibQueue.dequeue(queue, NULL);
    LibQueue.dequeue(queue, NULL);
    LibQueue.dequeue(queue, NULL);

    LibQueue.print(queue, print_int);
    LibQueue.enqueue_int(queue, 1);
    LibQueue.enqueue_int(queue, 1);
    LibQueue.enqueue_int(queue, 1);
    LibQueue.enqueue_int(queue, 1);
    LibQueue.print(queue, print_int);

    LibQueue.free(queue, NULL);
    return EXIT_SUCCESS;
}