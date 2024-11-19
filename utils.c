#include "utils.h"

void swap(int* a, int* b)
{
    int c = *b;
    *b = *a;
    *a = c;
    return;
}

void print_int(void* i)
{
    printf("%d ", *(int*)i);
    return;
}

void print_str(void* s)
{
    printf("%s ", (char*)s);
    return;
}

void* to_void(void* x, const size_t typeSize)
{
    void* converted = (void*)malloc(typeSize);
    memcpy(converted, x, typeSize);
    return converted;
}

void** array_to_void_array(void* arr, const size_t n, const size_t typeSize)
{
    void** array = (void**)malloc(sizeof(void*) * n);
    if (array == NULL)
    {
        return NULL;
    }

    unsigned char* bytes = arr;
    for (size_t i = 0; i < n; i++)
    {
        void* item = (void*)malloc(typeSize);
        if (item == NULL)
        {
            return NULL;
        }
        memcpy(item, bytes + (i * typeSize), typeSize);
        array[i] = item;
    }

    return array;
}


// frees void array created using convert_array
int free_void_array(void* arr[], size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        free(arr[i]);
    }
    free(arr);
    return EXIT_SUCCESS;
}