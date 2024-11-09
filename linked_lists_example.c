#include <stdio.h>
#include <stdlib.h>

#include "linked_lists.h"

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

    LinkedList* list = LibLinkedList.create_list(arr, n);

    LibLinkedList.print_list(list);
    printf("%d\n", list->itemCount);
    // basic uses of a linked list

    // LibLinkedList.insert(list, 50, -1);
    // LibLinkedList.insert(list, 10, 0);
    // LibLinkedList.insert(list, 43, 4);

    LibLinkedList.delete(list, -1);
    LibLinkedList.delete(list, -1);
    LibLinkedList.delete(list, 0);
    LibLinkedList.delete(list, -5);
    LibLinkedList.delete(list, 5);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -1);

    // LibLinkedList.print_list(list);
    // LibLinkedList.reverse(list);
    // LibLinkedList.print_list(list);

    free_list(list);

    return EXIT_SUCCESS;
}
