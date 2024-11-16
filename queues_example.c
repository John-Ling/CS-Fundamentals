#include <stdio.h>
#include <stdlib.h>

#include "queues.h"

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
    Queue* queue = LibQueue.create(arr, n);

    LibQueue.print(queue);


    LibQueue.dequeue(queue, NULL);
    LibQueue.dequeue(queue, NULL);
    LibQueue.dequeue(queue, NULL);
    LibQueue.dequeue(queue, NULL);
    LibQueue.dequeue(queue, NULL);
    LibQueue.dequeue(queue, NULL);
    LibQueue.dequeue(queue, NULL);
    LibQueue.dequeue(queue, NULL);

    LibQueue.print(queue);
    LibQueue.enqueue(queue, 1);
    LibQueue.enqueue(queue, 1);
    LibQueue.enqueue(queue, 1);
    LibQueue.enqueue(queue, 1);
    LibQueue.print(queue);

    LibQueue.free(queue);
    return EXIT_SUCCESS;
}