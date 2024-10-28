#include <stdio.h>
#include <stdlib.h>

// implementation of the bubble sort algorithm for learning purposes

int bubble_sort(int arr[], const int n);

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

    bubble_sort(arr, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}


int bubble_sort(int arr[], const int n)
{
    int upper = n - 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < upper; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int tmp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = tmp;
            }
        }
        upper--;
    }
    return EXIT_SUCCESS;
}