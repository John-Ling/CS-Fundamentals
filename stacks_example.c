#include <stdio.h>
#include <stdlib.h>

#include "stacks.h"
#include "utils.h"

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

    Stack* stack = LibStack.create(NULL, 0, sizeof(char*));

    // char* a = "John";
    // int a = 5;
    // void* x = (void*)a;
    // printf("%s\n", (char*)x);
    // for (int i = 0; i < 5; i++)
    // {
    //     void* x = s[i];
    //     printf("%c ", *(char*)x);
    // }
    // puts("Pushing onto stack");
    LibStack.push_str(stack, "Andrew");
    LibStack.push_str(stack, "Frank");
    LibStack.push_str(stack, "Jun An");

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
    LibStack.print(stack, print_str);

    LibStack.is_empty(stack);
    LibStack.pop(stack, NULL);

    puts("Printing");
    LibStack.print(stack, print_str);
    LibStack.free(stack);

    return EXIT_SUCCESS;
}