#include <stdio.h>
#include <stdlib.h>

#include "linked_lists.h"
#include "utils.h"

struct s {
        char* name;
        int isDead;
};

void print(void* a)
{
    struct s* b = (struct s*)a;
    printf("%s %d ", b->name, b->isDead);
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
    
    // void** a = CONVERT_ARRAY(arr, n);
    // LinkedList* list = LibLinkedList.create(array_to_void_array(arr, n, sizeof(int)), n);

    // idea implement easy insert macros for integers, chars, floats, arrays, 
    // impelemnt easy print macros overload both insert and print function

    LinkedList* list = LibLinkedList.create(NULL, 0, sizeof(struct s));
    struct s a;
    a.name = "John";
    a.isDead = 0;
    LibLinkedList.insert(list, &a, -1);
    a.name = "campbell";
    a.isDead = 0;
    LibLinkedList.insert(list, &a, -1);
    a.name = "uncle";
    a.isDead = 1;
    LibLinkedList.insert(list, &a, -1);
    // unsigned long a = 45;
    // printf("%d\n", sizeof(LinkedList));
    // LibLinkedList.print(list, print_int);
    // printf("%d\n", list->itemCount);
    // basic uses of a linked list

    // int ab = 50;
    // LibLinkedList.insert(list, &ab, -1);
    // ab = 40;
    // LibLinkedList.insert(list, &ab, 0);

    // float pi = 3.14;
    // LibLinkedList.insert(list, &pi, -1);

    // for (int i = 0; i < 10; i++)
    // {
    //     LibLinkedList.insert(list, &i, -1);
    // }
    // for (int i = 0; i < 10; i++)
    // {
    //     LibLinkedList.insert_int(list, i, -1);
    // }
    // LibLinkedList.insert(list, 43, 4);

    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, 0);
    // LibLinkedList.delete(list, 0);
    // LibLinkedList.delete(list, 0);
    // LibLinkedList.delete(list, 0);
    // LibLinkedList.delete(list, 0);
    // LibLinkedList.delete(list, 0);
    // LibLinkedList.delete(list, 0);
    // LibLinkedList.delete(list, 2);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -1);
    // LibLinkedList.delete(list, -5);
    // LibLinkedList.delete(list, 5);
    // for (int i = 0; i < 10; i++)
    // {
    //     LibLinkedList.delete(list, 0);
    //     printf("%d\n", list->itemCount);
    // }
    
    a.name = "grandpa";
    a.isDead = 1;
    LibLinkedList.insert(list, &a, -1);
    LibLinkedList.print(list, print);
    LibLinkedList.delete(list, -1);
    LibLinkedList.reverse(list);
    LibLinkedList.print(list, print);

    LibLinkedList.free(list);

    return EXIT_SUCCESS;
}