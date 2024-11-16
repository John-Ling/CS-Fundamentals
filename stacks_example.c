#include <stdio.h>
#include <stdlib.h>

#include "stacks.h"

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

    Stack* stack = LibStack.create(NULL, 0);
    LibStack.print(stack);
    puts("Pushing onto stack");
    LibStack.push(stack, 1);
    LibStack.push(stack, 2);
    LibStack.push(stack, 3);
    LibStack.push(stack, 4);
    

    LibStack.empty(stack);

    puts("Printing");
    LibStack.print(stack);
    LibStack.free(stack);

    return EXIT_SUCCESS;
}