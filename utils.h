#ifndef Utils_H
#define Utils_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* a, int* b);

enum Type
{
    STRING,
    INT
};

void** convert_array(void* arr, size_t n, const size_t typeSize);
void* convert(void* x, const size_t typeSize);
int free_void_array(void* arr[], size_t n);
// macro to allow conversion of any type array into void array
#define CONVERT_ARRAY(arr, n) convert_array((void*)arr, n, sizeof(typeof(*arr)))
#define CONVERT(x) convert((void*)x, sizeof(x))

#endif