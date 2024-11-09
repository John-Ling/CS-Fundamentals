#include <stdio.h>
#include <stdlib.h>

// implementation of binary search for learning purposes

int binary_search(int arr[], int search, int n);
int recursive_binary_search(int arr[], int search, int upperIndex, int lowerIndex);
int multi_key_binary_search(int arr[], const int search, const int n);

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf("Too few arguments\n");
        return EXIT_FAILURE;
    }

    int arr[argc - 2];

    for (int i = 1; i < argc - 1; i++)
    {
        arr[i - 1] = atoi(argv[i]);
    }

    const int search = atoi(argv[argc - 1]);
    binary_search(arr, search, argc - 2);
    recursive_binary_search(arr, search, argc - 2, 0);
    multi_key_binary_search(arr, search, argc - 2);

    return EXIT_SUCCESS;
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
            return EXIT_SUCCESS;
        }
    }
    printf("Could not find value\n");
    return EXIT_FAILURE;
}

// variation on binary search to find multiple instances of a value
// after each match linear search is performed upwards and downards
// since list is sorted adjacent elements will match the search
int multi_key_binary_search(int arr[], const int search, const int n)
{
    int upper = n - 1;
    int lower = 0;

    while (lower <= upper)
    {
        int mid = (upper + lower) / 2;
        if (search < arr[mid])
        {
            upper = mid - 1;
        }
        else if (search > arr[mid])
        {
            lower = mid + 1;
        }
        else 
        {
            printf("Found value at index %d\n", mid);
            int i = mid + 1;
            while (i < n && arr[i] == search)
            {
                printf("Found value at index %d\n", i);
                i++;
            }
            i = mid - 1;
            while (i >= 0 && arr[i] == search)
            {
                printf("Found value at index %d\n", i);
                i--;
            }
            return EXIT_SUCCESS;
        }
    }

    printf("Could not find value\n");
    return EXIT_FAILURE;
}

int recursive_binary_search(int arr[], int search, int upperIndex, int lowerIndex)
{
    if (lowerIndex > upperIndex)
    {
        printf("Could not find value\n");
        return EXIT_FAILURE;
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
        return EXIT_SUCCESS;
    }

    return recursive_binary_search(arr, search, upperIndex, lowerIndex);
}