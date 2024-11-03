#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// implementation of the BMH algorithm for learning purposes

int bmh(const char* string, const char* pattern);

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        return EXIT_FAILURE;
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
        bmh(strings[i], pattern);
    }

    for (int i = 0; i < argc - 2; i++)
    {
        free(strings[i]);
    }
    free(pattern);
    return EXIT_SUCCESS;
}

int bmh(const char* string, const char* pattern)
{
    const int patternLength = strlen(pattern);
    const int stringLength = strlen(string);

    // create shift vector/bad match table
    // a hash map could be used instead of an array however we're keeping it simple
    // also the original implementation didn't use a hash map
    int shiftArray[256] = {patternLength};
    for (int i = 0; i < patternLength; i++)
    {
        shiftArray[(int)pattern[i]] = patternLength - i - 1;
    }

    // perform the string search
    int pointerA = 0;
    int pointerB = patternLength;
    int found = 1;
    int i = 0;
    while (i < stringLength)
    {
        int k = patternLength - 1;
        int badCharacterIndex = 0;
        for (int j = pointerB - 1; j >= pointerA; j--)
        {
            if (string[j] != pattern[k])
            {
                found = 0;
                badCharacterIndex = j;
                break;
            }
            k--;
        }

        if (found)
        {
            printf("Found pattern at index %d\n", i);
        }
        else
        {
            // lookup in bad match table how many steps to move forward
            int offset = shiftArray[(int)string[badCharacterIndex]] - 1;`
            if (offset == -1)
            {
                offset = patternLength - 1;
            }
            i += offset;
            pointerA += offset;
            pointerB += offset;
        }

        found = 1;
        pointerA++;
        pointerB++;
        i++;
    }
    return EXIT_SUCCESS;
}