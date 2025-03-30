#include <stdio.h>
#include <stdlib.h>

#include "linked_lists.h"
#include "utils.h"

// example usage of the linked list library

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

    // create empty linked list of integers
    LinkedList* list = LibLinkedList.create(array_to_void_array(arr, n, sizeof(int)), n, sizeof(int));

    // insert values into linked list
    for (int i = 0; i < n; i++) 
    {
        printf("%d\n", arr[i]);
        LibLinkedList.insert_int(list, arr[i], -1);
    }

    // print linked list
    LibLinkedList.print(list, print_int);

    // reverse linked list
    LibLinkedList.reverse(list);

    // print linked list
    LibLinkedList.print(list, print_int);

    LibLinkedList.free(list, default_free);
    return EXIT_SUCCESS;
}