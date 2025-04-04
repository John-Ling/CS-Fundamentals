#include <stdio.h>
#include <stdlib.h>

#include "quicksort.h"
#include "utils.h"

// (very naive) implementation of the quicksort algorithm for learning purposes

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        puts("Pass values to form the array");
        return EXIT_FAILURE;
    }
    const int n = argc - 1;

    int arr[n];
    for (int i = 1; i < argc; i++)
    {
        arr[i - 1] = atoi(argv[i]);
    }

    // printf("%d\n", lomuto_partition(arr, 0, n - 1));
    quicksort(arr, n);
    

    puts("Sorted");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    putchar('\n');
    return EXIT_SUCCESS;
}

// interface to sort() that only requires array
// and size variable
int quicksort(int arr[], const int n)
{
    if (n < 0)
    {
        return EXIT_FAILURE;
    }

    if (n <= 1)
    {
        // empty or 1 item array
        return EXIT_SUCCESS;
    }

    return sort(arr, 0, n - 1);
}

// implementation of quicksort for use with quicksort()
static int sort(int arr[], const int lowerIndex, const int upperIndex)
{
    int pivotIndex = lomuto_partition(arr, lowerIndex, upperIndex);

    // run quicksort on left subarray
    quicksort(arr, pivotIndex);

    // run quicksort on right subarray
    quicksort(arr, upperIndex - pivotIndex);
    return EXIT_SUCCESS;
}

static int lomuto_partition(int arr[], const int lowerIndex, const int upperIndex)
{
    // lomuto partitioning works on the assumption that
    // the pivot is the end of the array
    const int pivot = upperIndex;
    const int pivotValue = arr[pivot];
    
    // create two pointers to the lower area
    int i = lowerIndex; // i represents the next position to move the smaller item
    int j = lowerIndex;
    
    while (j <= upperIndex - 1)
    {
        if (arr[j] <= pivotValue)
        {
            // swap smaller item from wrong position j
            // to correct position i
            swap(&arr[j], &arr[i]);
            i++; // increment i to next position for smaller item
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