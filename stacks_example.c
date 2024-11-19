#include <stdio.h>
#include <stdlib.h>

#include "stacks.h"

void* int_to_void(int x)
{
    void* ptr = NULL;
    memcpy(ptr, &x, sizeof(x));
    return ptr;
}

int main(int argc, char* argv[])
{   
    // if (argc == 1)
    // {
    //     printf("Pass values to form the array\n");
    //     return EXIT_FAILURE;
    // }
    // const int n = argc - 1;

    // int arr[n];
    // for (int i = 1; i < argc; i++)
    // {
    //     arr[i - 1] = atoi(argv[i]);
    // }

    Stack* stack = LibStack.create(NULL, 0, sizeof(int));

    // char* a = "John";
    int a = 5;
    // void* x = (void*)a;
    // printf("%s\n", (char*)x);
    // for (int i = 0; i < 5; i++)
    // {
    //     void* x = s[i];
    //     printf("%c ", *(char*)x);
    // }
    // puts("Pushing onto stack");
    LibStack.push(stack, (void*)a);
    // a = "Andrew";
    a = 1;
    LibStack.push(stack, (void*)a);
    // a = "Jun An";
    a = 3;
    LibStack.push(stack, (void*)a);
    // a = "Campbell";
    a = 1;
    LibStack.push(stack, (void*)a);
    // a  "Frank";
    a = 2;
    LibStack.push(stack, (void*)a);

    // a = 2;
    // LibStack.push(stack, &a);
    // a = 3;
    // LibStack.push(stack, &a);
    // a = 4;
    // LibStack.push(stack, &a);

    // LibStack.push(stack, int_to_void(1));
    // LibStack.push(stack, CONVERT(2));
    // LibStack.push(stack, CONVERT(3));
    // LibStack.push(stack, CONVERT(4));
    puts("Printing");
    LibStack.print(stack, print_int);

    LibStack.is_empty(stack);

    puts("Printing");
    LibStack.print(stack, print_int);
    LibStack.free(stack);

    return EXIT_SUCCESS;
}