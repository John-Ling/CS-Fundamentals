#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

// implementation of the mergesort algorithm for learning purposes

int merge_sort(int arr[], const int lowerIndex, const int upperIndex);
static int merge(int arr[], const int lowerIndex, const int middleIndex, 
                const int upperIndex);

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

    merge_sort(arr, 0, n - 1);    

    puts("Sorted");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    putchar('\n');
    return EXIT_SUCCESS;
}

// perform merge sort on arr using upper and lower indexes for efficiency
int merge_sort(int arr[], const int lowerIndex, const int upperIndex)
{
    if (lowerIndex > upperIndex)
    {
        return EXIT_FAILURE;
    }

    // base case
    if (upperIndex + 1 - lowerIndex == 1)
    {
        // array is of length 1 which we cannot halve anymore
        return EXIT_SUCCESS;
    }

    // divide array into half
    const int middleIndex = (lowerIndex + upperIndex) / 2;

    // run merge sort on left subarray
    merge_sort(arr, lowerIndex, middleIndex);

    // run merge sort on right subarray
    merge_sort(arr, middleIndex + 1, upperIndex);

    // sort and merge subarrays
    merge(arr, lowerIndex, middleIndex, upperIndex);
    return EXIT_SUCCESS;
}

// creates 2 temporary sub arrays and merges them
// by writing the values back into the correct 
// positions in array in ascending order
static int merge(int arr[], const int lowerIndex, const int middleIndex, 
                const int upperIndex)
{
    if (lowerIndex > upperIndex)
    {
        return EXIT_FAILURE;
    }

    // temporary arrays to store our subarrays
    int left[1 + middleIndex - lowerIndex];
    int leftPointer = 0; // pointer to next index in left
    int right[1 + upperIndex - middleIndex];
    int rightPointer = 0; // pointer to next index in right

    // write data to left and right subarrays
    for (int i = lowerIndex; i <= upperIndex; i++)
    {
        if (i > middleIndex)
        {
            right[rightPointer] = arr[i];
            rightPointer++;
        }
        else
        {
            left[leftPointer] = arr[i];
            leftPointer++;
        }
    }

    const int leftCount = leftPointer;
    leftPointer = 0;
    const int rightCount = rightPointer;
    rightPointer = 0;

    int currentPointer = lowerIndex; // pointer to next index in arr

    // merge
    while (leftPointer < leftCount && rightPointer < rightCount)
    {
        int lesser;
        if (left[leftPointer] < right[rightPointer])
        {
            lesser = left[leftPointer];
            leftPointer++;
        }
        else
        {
            lesser = right[rightPointer];
            rightPointer++; 
        }

        // write lesser value back into array
        arr[currentPointer] = lesser;
        currentPointer++;
    }

    // write remaining elements in either left or right array
    while (leftPointer < leftCount)
    {
        arr[currentPointer] = left[leftPointer];
        leftPointer++;
        currentPointer++;
    }

    while (rightPointer < rightCount)
    {
        arr[currentPointer] = right[rightPointer];
        rightPointer++;
        currentPointer++;
    }

    return EXIT_SUCCESS;
}