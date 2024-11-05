#include <stdio.h>
#include <stdlib.h>

#include "quicksort.h"
#include "utils.h"

// (very naive) implementation of the quicksort algorithm for learning purposes

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

    // naive_quicksort(arr, n);
    // printf("%d\n", partition(arr, n, 0, n));
    // printf("%d\n", lomuto_partition(arr, 0, n - 1));

    quicksort(arr, n, 0, n - 1);

    printf("Sorted\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}

// an actual implementation if quicksort after seeing an implementation
int quicksort(int arr[], const int n, int lower, int upper)
{
    if (n < 0)
    {
        return EXIT_FAILURE;
    }

    // sorting a empty or 1 element array is instant
    if (n < 1)
    {
        return EXIT_SUCCESS;
    }

    if (lower < upper)
    {
        int pivotIndex = lomuto_partition(arr, lower, upper);

        // run quicksort on left subarray
        quicksort(arr, n, lower, pivotIndex - 1);

        // run quicksort on right subarray
        quicksort(arr, n, pivotIndex + 1, upper);
    }

    return EXIT_SUCCESS;
}

static int lomuto_partition(int arr[], int low, int high)
{
    // lomuto partitioning works on the assumption that
    // the pivot is the end of the array
    const int pivot = high;
    const int pivotValue = arr[pivot];
    
    // create two pointers to the lower area
    int i = low; // i represents the next position to move the smaller item
    int j = low;
    
    while (j <= high - 1)
    {
        if (arr[j] <= pivotValue)
        {
            // swap smaller item from wrong position j
            // to correct position i
            swap(&arr[j], &arr[i]);

            // increment i to next position for smaller item
            i++; 
        }
        j++;
    }

    // at the end the value of i will be the correct position
    // of the pivot so we move the pivot into ith index
    swap(&arr[pivot], &arr[i]);
    return i; // return index of the pivot
}

// pivot functions
static int first_item_pivot(const int n)
{
    return n - n;
}

static int last_item_pivot(const int n)
{
    return n - 1;
}

static int middle_item_pivot(const int n)
{
    return n / 2;
}

static int random_pivot( const int n)
{
    return rand() % n;
}

// efficient way of finding median of 3 integers using xor
static int median_of_three(int arr[], const int n)
{
    const int first = arr[0];
    const int middle = arr[n / 2];
    const int last = arr[n - 1];

    // check if first is bigger than middle or bigger than last
    if ((first > middle) ^ (first > last))
    {
        return first;
    }
    else if ((middle < first) ^ (middle < last))
    {
        return middle;
    }

    return last;
}