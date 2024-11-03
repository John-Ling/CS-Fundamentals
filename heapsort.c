#include <stdio.h>
#include <stdlib.h>

// implementation of the heapsort algorithm for learning purposes

static int heapify(int arr[], int n);
static int swap(int* a, int* b);
static int sift_down(int arr[], int n, int i );
int heapsort(int arr[], const int n);

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
    
    heapsort(arr, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}

int heapsort(int arr[], const int n)
{
    // create max heap 
    heapify(arr, n);

    int i = 0;
    while (i < n)
    {   
        // first item in heapified array
        // will be biggest or smallest value depending if max or min heap is used

        // move item to end of array to exclude it from future runs of heapify
        swap(&arr[0], &arr[n - i - 1]);
        i++;

        // heap is now damaged since we swapped the root with another value
        // run sift down to move value down into it's proper place
        sift_down(arr, n - i, 0);
        // heap has been rebuilt start again
    }
    return EXIT_SUCCESS;
}

// build a max heap from an unsorted array
static int heapify(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        sift_down(arr, n, i);
    }
    return EXIT_SUCCESS;
}

// rebuild the max heap after the root or any single node is moved
// this function is called sift down since it works by moving the improper root
// down the heap into its proper place
static int sift_down(int arr[], int n, int i )
{
    int largestIndex = i;
    int leftIndex = 2 * i + 1;
    int rightIndex = 2 * i + 2;

    // determine whether left or right item is bigger than root 
    if (leftIndex < n && arr[leftIndex] > arr[largestIndex])
    {
        largestIndex = leftIndex;
    }
    
    if (rightIndex < n && arr[rightIndex] > arr[largestIndex])
    {
        largestIndex = rightIndex;
    }

    if (largestIndex != i)
    {
        swap(&arr[i], &arr[largestIndex]);
        sift_down(arr, n, largestIndex);
    }
    return EXIT_SUCCESS;
}

static int swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return EXIT_SUCCESS;
}