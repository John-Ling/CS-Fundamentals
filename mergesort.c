#include <stdio.h>
#include <stdlib.h>

// implementation of the mergesort algorithm for learning purposes

int main(int argc, char* argv[])
{
    return EXIT_SUCCESS;
}

int merge_sort(int arr[], const int n, int lower, int upper)
{
    // partition the array into halves
    int half = n / 2;
    
    if (half == lower)
    {
        // left half has been reduced to 2 items
        if (arr[half] > arr[lower])
        {

        }
    }
    else if (half == upper)
    {
        // right half has been reduced to 2 items
    }

    if (half == lower || half == upper)
    {
        // no further halves can be created

    }


    // perform merge sort on left half
    merge_sort(arr, n, lower, half);

    // perform merge sort on right half
    merge_sort(arr, n, half + 1, upper);

    return EXIT_SUCCESS;
}

static int merge(int arr[], const int n, int lower, int upper)
{
    
    return EXIT_SUCCESS;
}