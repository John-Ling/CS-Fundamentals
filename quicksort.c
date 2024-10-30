#include <stdio.h>
#include <stdlib.h>

// (very naive) implementation of the quicksort algorithm for learning purposes

int quicksort(int arr[], int n);
int partition(int arr[], int n);

#define N 10

int main(int argc, char* argv[])
{
    int arr[N] = {2, 40, 10, 80, 30, 90, 40, 50, 60, 5 };
    quicksort(arr, N);
    printf("Sorted\n");
    for (int i = 0; i < N; i++)
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

    const int PIVOT_VALUE = arr[upper - 1];

    while (next < upper)
    {
        if (arr[next] < PIVOT_VALUE)
        {
            int tmp = arr[lower];
            arr[lower] = arr[next];
            arr[next] = tmp;
            lower++;
            next++;
        }
        else if (arr[next] > PIVOT_VALUE)
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

int lomuto_partition(int arr[], int n)
{
    return EXIT_SUCCESS;
}