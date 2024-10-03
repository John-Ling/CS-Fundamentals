#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int create_failure_array(int lps[], const char* pattern, const int length);
int kmp_search(const char* pattern, const char* string);

int main(int argc, char* argv[])
{
    const char* pattern = "ABCDABD";
    const char* string = "ABC ABCDAB ABCDABCDABDE";
    kmp_search(pattern, string);
    return 0;
}

int kmp_search(const char* pattern, const char* string)
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
        int k = 0;
        for (int j = pointerA; j < pointerB; j++)
        {
            if (string[j] == pattern[k])
            {
                k++;
                continue;
            }
            found = 0;
            i = j - lps[k] - 1; // skip over by setting index
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
    return 0;
}

// I'll be honest I don't fully understand how this works
// I just took the code from geeksfromgeeks, ran it through claude and adjusted a bit
// general idea still applies just a abstract way of implementing it I guess
int create_failure_array(int lps[], const char* pattern, const int length)
{
    if (length <= 0)
    {
        return 1;
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

    return 0;
}
