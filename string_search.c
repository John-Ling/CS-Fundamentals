#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int naive_pattern_search(const char* string,const char* pattern);
int build_lps_array(const char* pattern, int M, int prefixTable[]);

int main(int argc, char* argv[])
{
    char* string = "AABAACAADAABAABA";
    char* pattern = "AABA";
    // naive_pattern_search(string, pattern);

    int prefixTable[4];
    build_lps_array(pattern, 4, prefixTable);
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", prefixTable[i]);
    }
    printf("\n");

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

int naive_kmp(const char* string, const char* pattern)
{
    int pointerA;
    int pointerB = strlen(pattern);

}

int build_lps_array(const char* pattern, int M, int prefixTable[])
{
    prefixTable[0] = -1; // an empty string has no proper prefix
    int lpsLength = 0; // longest proper prefix length
    // Loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        printf("%c %c\n", pattern[i], pattern[lpsLength]);
        if (pattern[i] == pattern[lpsLength]) {
            printf("Equal\n");
            lpsLength++;
            prefixTable[i] = lpsLength;
            i++;
        }
        else {
            if (lpsLength != 0) {
                printf("Setting new length\n");
                lpsLength = prefixTable[lpsLength - 1];
            }
            else {
                printf("Resetting %d\n", i);
                prefixTable[i] = 0;
                i++;
            }
        }
    }
    return 0;
}