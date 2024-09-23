#include <stdio.h>

int binary_search(int arr[], int search, int n);
int recursive_binary_search(int arr[], int search, int upperIndex, int lowerIndex);

#define N 10

int main(void)
{
    int arr[N] = {12, 12, 32, 48, 54, 55, 76, 87, 89, 90};
    binary_search(arr, 87, N);
    recursive_binary_search(arr, 87, N - 1, 0);
    return 0;
}

int binary_search(int arr[], int search, int n)
{    
    int upperIndex = n - 1;
    int lowerIndex = 0;

    while (lowerIndex != upperIndex)
    {
        int middleIndex = (upperIndex + lowerIndex) / 2;
        if (search > arr[middleIndex])
        {
            lowerIndex = middleIndex;
        }
        else if (search < arr[middleIndex])
        {
            upperIndex = middleIndex;
        }
        else
        {
            printf("Found value at index %d\n", middleIndex);
            return 0;
        }
    }
    printf("Could not find value\n");
    return 1;
}

int recursive_binary_search(int arr[], int search, int upperIndex, int lowerIndex)
{
    if (upperIndex == lowerIndex)
    {
        printf("Could not find value\n");
        return 1;
    }

    int middleIndex = (upperIndex + lowerIndex) / 2;

    if (search > arr[middleIndex])
    {
        lowerIndex = middleIndex;
    }
    else if (search < arr[middleIndex])
    {
        upperIndex = middleIndex;
        
    }
    else
    {
        printf("Found value at index %d\n", middleIndex);
        return 0;
    }

    recursive_binary_search(arr, search, upperIndex, lowerIndex);
    return 0;
}