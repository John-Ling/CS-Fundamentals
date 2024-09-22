#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int create_failure_array(int* lps, const char* pattern, const int length);
int main(int argc, char* argv[])
{
    char* pattern = "ABCDABD";
    const int length = strlen(pattern);
    int* lps = (int*)malloc(sizeof(int) * length);
    create_failure_array(lps, pattern, length);

    for (int i = 0; i < length; i++)
    {
        printf("%d ", lps[i]);
    }
    printf("\n");
    free(lps);
    return 0;
}

int kmp_search(const char* pattern, const char* string)
{
    return 0;
}

// I'll be honest I don't fully understand how this works
// I just took the code from geeksfromgeeks, ran it through claude and adjusted a bit
// general idea still applies just a abstract way of implementing it I guess
int create_failure_array(int* lps, const char* pattern, const int length)
{
    if (length <= 0)
        return 1;

    lps[0] = -1;

    int i = 0;
    int j = -1; // length of longest prefix suffix
    while (i < length - 1)
    {
        printf("i %d j %d\n", i, j);
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

    return 0;
}
