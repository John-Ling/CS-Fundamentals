#include <stdio.h>
#include <stdlib.h>

#include "linked_lists.h"
#include "utils.h"

void print_int(void* i)
{
    printf("%d ", *(int*)i);
    return;
}

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

    // the idea
    // should be able to pass

    // void** a = CONVERT_ARRAY(arr, n);
    // LinkedList* list = LibLinkedList.create(array_to_void_array(arr, n, sizeof(int)), n);
    LinkedList* list = LibLinkedList.create(NULL, 0);
    printf("%d\n", sizeof(LinkedList));
    // LibLinkedList.print(list, print_int);
    // printf("%d\n", list->itemCount);
    // basic uses of a linked list

    int ab = 50;
    LibLinkedList.insert(list, &ab, -1);
    ab = 40;
    LibLinkedList.insert(list, &ab, 0);
    // LibLinkedList.insert(list, 43, 4);

    LibLinkedList.delete(list, -1);
    LibLinkedList.delete(list, 0);
    LibLinkedList.delete(list, 0);
    LibLinkedList.delete(list, 0);
    LibLinkedList.delete(list, 0);
    LibLinkedList.delete(list, 0);
    LibLinkedList.delete(list, 0);
    LibLinkedList.delete(list, 0);
    LibLinkedList.delete(list, 2);
    LibLinkedList.delete(list, -1);
    LibLinkedList.delete(list, -1);
    LibLinkedList.delete(list, -1);
    LibLinkedList.delete(list, -5);
    LibLinkedList.delete(list, 5);
    for (int i = 0; i < 10; i++)
    {
        LibLinkedList.delete(list, 0);
        printf("%d\n", list->itemCount);
    }
    
    LibLinkedList.print(list, print_int);
    LibLinkedList.reverse(list);
    LibLinkedList.print(list, print_int);

    LibLinkedList.free(list);

    return EXIT_SUCCESS;
}