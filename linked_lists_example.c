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


    // can either overload functions
    // overloaded functions then do conversions into void pointer and pass to create 

    // LinkedList* list = LibLinkedList.create(piss, n, INT);
    LinkedList* list = LibLinkedList.create(CONVERT_ARRAY(arr, n), n);
    LibLinkedList.print(list, print_int);
    printf("%d\n", list->itemCount);
    // basic uses of a linked list

    int a = 50;
    LibLinkedList.insert(list, &a, -1);
    a = 40;
    LibLinkedList.insert(list, &a, 0);
    // LibLinkedList.insert(list, 43, 4);

    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, 0);
    // LibLinkedList.delete(list, 2);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -5);
    // LibLinkedList.delete(list, 5);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -1);

    LibLinkedList.print(list, print_int);
    LibLinkedList.reverse(list);
    LibLinkedList.print(list, print_int);

    LibLinkedList.free(list);

    return EXIT_SUCCESS;
}