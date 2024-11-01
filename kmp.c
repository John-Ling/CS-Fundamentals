#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// implementation of the kmp algorithm for learning purposes

static int create_failure_array(int lps[], const char* pattern, const int length);
int kmp_search(const char* string, const char* pattern);

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
        kmp_search(strings[i], pattern);
    }
    
    for (int i = 0; i < argc - 2; i++)
    {
        free(strings[i]);
    }
    free(pattern);

    return EXIT_SUCCESS;
}

int kmp_search(const char* string, const char* pattern)
{
    const int patternLength = strlen(pattern);
    const int stringLength = strlen(string);
    int lps[patternLength];
    create_failure_array(lps, pattern, patternLength);
    
    int i = 0;
    int found = 1;

    int pointerA = 0;
    int pointerB = patternLength;
    while (i < stringLength)
    {
        for (int j = pointerA; j < pointerB; j++)
        {
            if (string[j] == pattern[j - pointerA])
            {
                continue;
            }
            found = 0;
            i = j - lps[j - pointerA] - 1; // skip over by setting index
            break;
        }

        if (found)
        {
            printf("Found pattern at index %d\n", i);
        }

        found = 1;
        pointerA++;
        pointerB++;
        i++;
    }
    return EXIT_SUCCESS;
}

// I'll be honest I don't fully understand how this works
// I just took the code from geeksfromgeeks, ran it through claude and adjusted a bit
// general idea still applies just an abstract way of implementing it I guess
static int create_failure_array(int lps[], const char* pattern, const int length)
{
    if (length <= 0)
    {
        return EXIT_FAILURE;
    }
            
    lps[0] = -1;

    int i = 0;
    int j = -1; // length of longest prefix suffix
    while (i < length - 1)
    {
        if (j == -1 || pattern[i] == pattern[j])
        {
            // either initialise value at index i as 0
            // or increment previous value and save it in next
            j++;
            i++;
            lps[i] = j;
        }
        else
        {
            // reset 
            j = lps[j];
        }        
    }

    return EXIT_SUCCESS;
}
