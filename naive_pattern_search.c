#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int naive_pattern_search(const char* string, const char* pattern);

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
        naive_pattern_search(strings[i], pattern);
    }
    

    for (int i = 0; i < argc - 2; i++)
    {
        free(strings[i]);
    }
    free(pattern);
    
    return 0;
}

int naive_pattern_search(const char* string, const char* pattern)
{
    int stringLength = strlen(string);

    int pointerA = 0;
    int pointerB = strlen(pattern);

    int found = 1;
    for (int i = 0; i < stringLength; i++)
    {
        int k = 0;
        for (int j = pointerA; j < pointerB; j++)
        {
            if (string[j] != pattern[k])
            {
                found = 0;
                break;
            }
            k++;
        }

        if (found)
        {
            printf("Found pattern at index %d\n", i);
        }

        found = 1;
        pointerA++;
        pointerB++;
    }
    return 0;
}