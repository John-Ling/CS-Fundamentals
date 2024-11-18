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

void** array_to_void_array(void* arr, const size_t n, const size_t typeSize);
void* convert(void* x, const size_t typeSize);
int free_void_array(void* arr[], size_t n);

#endif