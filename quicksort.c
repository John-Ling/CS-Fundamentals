#include <stdio.h>
#include <stdlib.h>

#include "quicksort.h"

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

    quicksort(arr, n);

    printf("Sorted\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}

int quicksort(int arr[], int n)
{
    if (n <= 1)
    {
        return EXIT_SUCCESS;
    }
    int pivotIndex = partition(arr, n);
    int itemsToLeft = pivotIndex;
    int itemsToRight = n - itemsToLeft - 1;
    int leftArr[itemsToLeft];
    int rightArr[itemsToRight];

    for (int i = 0; i < itemsToLeft; i++)
    {
        leftArr[i] = arr[i];
    }

    for (int i = 0; i < itemsToRight; i++)
    {
        rightArr[i] = arr[i + pivotIndex + 1];
    }

    // perform quicksort on the left
    quicksort(leftArr, itemsToLeft);
    for (int i = 0; i < itemsToLeft; i++) // copy data back into the original array 
    {
        arr[i] = leftArr[i];
    }

    // perform quicksort on the right
    quicksort(rightArr, itemsToRight);
    for (int i = 0; i < itemsToRight; i++)
    {
        arr[i + pivotIndex + 1] = rightArr[i];
    }
    return EXIT_SUCCESS;
}

int partition(int arr[], int n)
{
    int next = 0;
    int lower = 0;
    int upper = n;

    const int pivotValue = select_pivot(arr, n);

    while (next < upper)
    {
        if (arr[next] < pivotValue)
        {
            int tmp = arr[lower];
            arr[lower] = arr[next];
            arr[next] = tmp;
            lower++;
            next++;
        }
        else if (arr[next] > pivotValue)
        {
            int tmp = arr[upper - 1];
            arr[upper - 1] = arr[next];
            arr[next] = tmp;
            upper--;
        }
        else
        {
            next++;
        }
    }
    // return the index of the pivot
    return lower;
}

// pivot functions
static int first_item_pivot(int arr[], const int n)
{
    return arr[n - n];
}

static int last_item_pivot(int arr[], const int n)
{
    return arr[n - 1];
}

static int middle_item_pivot(int arr[], const int n )
{
    return arr[n / 2];
}

static int random_pivot(int arr[], const int n)
{
    return arr[rand() % n];
}

// efficient way of finding median of 3 integers using xor
// median is middle number when sorted
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


