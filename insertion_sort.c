#include <stdio.h>
#include <stdlib.h>

int insertion_sort(int arr[], int n);
int swap(int* a, int* b);

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf("Pass values to form the array\n");
        return 1;
    }
    const int n = argc - 1;

    int arr[n];
    for (int i = 1; i < n; i++)
    {
        arr[i - 1] = atoi(argv[i]);
    }
    insertion_sort(arr, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

int insertion_sort(int arr[], int n)
{
   for (int i = 1; i < n; i++)
    {
        int j = i;
        while (j > 0 && arr[j] < arr[j - 1])
        {
            int tmp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = tmp;
            j--;
        }
    }

    return 0;
}