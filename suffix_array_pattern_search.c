#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// implementation of very naive pattern searching using suffix arrays for learning purposes

#include "suffix_array_pattern_search.h"

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        return 1;
    }

    char* strings[argc - 2];
    for (int i = 1; i < argc - 1; i++)
    {
        const int length = strlen(argv[i]);
        strings[i - 1] = (char*)malloc(sizeof(char) * length);
        strncpy(strings[i - 1], argv[i], length);
    }

    const int patternLength = strlen(argv[argc - 1]);
    char* pattern = (char*)malloc(sizeof(char) * patternLength);
    strncpy(pattern, argv[argc - 1], patternLength);

    for (int i = 0; i < argc - 2; i++)
    {
        const int length = strlen(strings[i]);
        int suffixArray[length];
        generate_suffixes(suffixArray, strings[i]);
        suffix_search(strings[i], pattern, suffixArray, length);
    }

    for (int i = 0; i < argc - 2; i++)
    {
        free(strings[i]);
    }
    free(pattern);

    return 0;
}

// perform pattern searching via a suffix array and binary search
int suffix_search(char* string, const char* pattern, int suffixArray[], const int n)
{
    int upper = n - 1;
    int lower = 0;
    const int patternLength = strlen(pattern);

    while (lower <= upper)
    {
        int mid = (upper + lower) / 2;
        int suffixOffset = suffixArray[mid];
        char* suffix = string + suffixOffset;
        int result = strncmp(suffix, pattern, patternLength);
        if (result > 0)
        {
            upper = mid - 1;
        }
        else if (result < 0)
        {
            lower = mid + 1;
        }
        else
        {
            printf("Found pattern at index %d\n", suffixOffset);
            int i = mid + 1;
            suffixOffset = suffixArray[i];
            suffix = string + suffixOffset;
            while (i < n && strncmp(suffix, pattern, patternLength) == 0)
            {
                printf("Found pattern at index %d\n", suffixOffset);
                i++;
                suffixOffset = suffixArray[i];
                suffix = string + suffixOffset;
            }

            i = mid - 1;
            suffixOffset = suffixArray[i];
            suffix = string + suffixOffset;
            while (i >= 0 && strncmp(suffix, pattern, patternLength) == 0)
            {
                printf("Found pattern at index %d\n", suffixOffset);
                i--;
                suffixOffset = suffixArray[i];
                suffix = string + suffixOffset;
            }
            return 0;
        }
    }
    return 0;
}

int generate_suffixes(int suffixArray[], const char* string)
{
    const int length = strlen(string);
    suffix temp[length]; // temporary array for storing and sorting suffixes

    for (int i = 0; i < length; i++)
    {
        suffix suffix;
        suffix.suffix = (char*)malloc(sizeof(char) * (length - i + 1));
        if (suffix.suffix == NULL)
        {
            return 1;
        }
        suffix.startIndex = i;

        suffix.suffix[0] = string[0];
        for (int j = i; j < length; j++)
        {
            suffix.suffix[j - i] = string[j];
        }
        suffix.suffix[length - i] = '\0';
        temp[i] = suffix;
    }

    qsort(temp, length, sizeof(suffix), compare_suffixes);

    for (int i = 0; i < length; i++)
    {
        suffixArray[i] = temp[i].startIndex;
        free(temp[i].suffix);
    }

    return 0;
}

static int compare_suffixes(const void* a, const void* b)
{
    suffix A = *(suffix*)a;
    suffix B = *(suffix*)b;
    return strcmp(A.suffix, B.suffix);
}