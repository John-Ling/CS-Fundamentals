#include <stdio.h>
#include <stdlib.h>

int binary_search(int arr[], int search, int n);
int recursive_binary_search(int arr[], int search, int upperIndex, int lowerIndex);

#define N 10

int main(int argc, char* argv[])
{
    if (argc > N + 1)
    {
        printf("Too many arguments\n");
        return 1;
    }

    if (argc == 1)
    {
        printf("Too few arguments\n");
        return 1;
    }

    int arr[N] = {12, 12, 32, 48, 54, 55, 76, 87, 89, 90};

    for (int i = 1; i < argc; i++)
    {
        int search = atoi(argv[i]);
        binary_search(arr, search, N);
        recursive_binary_search(arr, search, N - 1, 0);
    }

    return 0;
}

int binary_search(int arr[], int search, int n)
{    
    int upperIndex = n - 1;
    int lowerIndex = 0;

    while (lowerIndex <= upperIndex)
    {
        int middleIndex = (upperIndex + lowerIndex) / 2;
        if (search > arr[middleIndex])
        {
            lowerIndex = middleIndex + 1;
        }
        else if (search < arr[middleIndex])
        {
            upperIndex = middleIndex - 1;
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
    if (lowerIndex > upperIndex)
    {
        printf("Could not find value\n");
        return 1;
    }

    int middleIndex = (upperIndex + lowerIndex) / 2;

    if (search > arr[middleIndex])
    {
        lowerIndex = middleIndex + 1;
    }
    else if (search < arr[middleIndex])
    {
        upperIndex = middleIndex - 1;
    }
    else
    {
        printf("Found value at index %d\n", middleIndex);
        return 0;
    }

    recursive_binary_search(arr, search, upperIndex, lowerIndex);
    return 0;
}