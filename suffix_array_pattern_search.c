#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int generate_suffixes(int suffixArray[], const char* string);

int main(int argc, char* argv[])
{
    const char* string = "banana";
    int suffixArray[6];
    generate_suffixes(suffixArray, string);
    for (int i = 0; i < 6; i++)
    {
        printf("%d ", suffixArray[i]);
    }
    printf("\n");
    return 0;
}

int generate_suffixes(int suffixArray[], const char* string)
{
    typedef struct 
    {
        char* suffix;
        int startIndex;
    } suffix;

    int compare_suffixes(const void* a, const void* b)
    {
        suffix A = *(suffix*)a;
        suffix B = *(suffix*)b;
        return strcmp(A.suffix, B.suffix);
    }

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
    }

    return 0;
}