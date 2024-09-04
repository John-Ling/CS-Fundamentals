#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int naive_pattern_search(const char* string,const char* pattern);

int main(int argc, char* argv[])
{
    char* string = "AABAACAADAABAABA";
    char* pattern = "AABA";
    naive_pattern_search(string, pattern);
    return 0;
}

int naive_pattern_search(const char* string, const char* pattern)
{
    int n = strlen(string);

    int pointerA = 0;
    int pointerB = strlen(pattern);

    int found = 1;
    for (int i = 0; i < n; i++)
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