#include <stdio.h>
#include <stdlib.h>

// implementation of linear search for learning purposes

int linear_search(int arr[], const int n, const int search);

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf("Too few arguments\n");
        return EXIT_FAILURE;
    }

    int arr[argc - 2];

    for (int i = 1; i < argc - 1; i++)
    {
        arr[i - 1] = atoi(argv[i]);
    }

    const int search = atoi(argv[argc - 1]);
    linear_search(arr, argc - 2, search);

    return EXIT_SUCCESS;
}

int linear_search(int arr[], const int n, const int search)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[n] == search)
        {
            printf("Found at index %d\n", i);
            return EXIT_SUCCESS;
        }
    }

    return EXIT_FAILURE;
}