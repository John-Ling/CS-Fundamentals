#include "utils.h"

void swap(int* a, int* b)
{
    int c = *b;
    *b = *a;
    *a = c;
    return;
}

void default_free(void* value)
{
    free(value);
    value = NULL;
    return;
}



void print_int(const void* i)
{
    printf("%d ", *(int*)i);
    return;
}

void print_str(const void* s)
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

int compare_int(const void* a, const void* b)
{
    if (*(int*)a == *(int*)b)
    {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int compare_str(const void* a, const void* b)
{
    char* s1 = (char*)a;
    char* s2 = (char*)b;

    while (1)
    {
        if (!*s1 && !*s2)
        {
            // both strings have finished at the same time
            break;
        }

        if ((!*s1 && *s2) || (*s1 && !*s2))
        {
            return EXIT_FAILURE;
        }

        if (*s1 != *s2)
        {
            return EXIT_FAILURE;
        }
        s1++;
        s2++;
    }

    // success
    return EXIT_SUCCESS;
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