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

void default_free(void* value);
void print_int(const void* i);
void print_str(const void* s);
void** array_to_void_array(void* arr, const size_t n, const size_t typeSize);
int free_void_array(void* arr[], size_t n);

#define CONVERT_ARRAY(arr, n) array_to_void_array((void*)arr, n, sizeof(typeof(*arr)))

#endif