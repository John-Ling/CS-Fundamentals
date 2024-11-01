#include <stdio.h>
#include <stdlib.h>

// implementation of the heapsort algorithm for learning purposes

static int heapify(int arr[], int n, int i);
static int swap(int* a, int* b);
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

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
    
    // heapsort(arr, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}

int heapsort(int arr[], const int n)
{
    int i = 0;
    while (i < n)
    {
        // create max heap
        heapify(arr, n - i, 0);
        for (int j = 0; j < n; j++)
        {
            printf("%d ", arr[j]);
        }
        printf("\n");

        printf("Got value %d\n", arr[0]);
    
        // move item to end of array to exclude it from future runs of heapify
        swap(&arr[0], &arr[n - i - 1]);
        i++;
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

// used to rebuild the max heap after the root is moved
// or used to generate 
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