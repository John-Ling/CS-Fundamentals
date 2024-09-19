#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fills lps[] for given pattern pat
void computeLPSArray(const char* pat, int M, int* lps)
{
    // Length of the previous longest prefix suffix
    int len = 0;

    // lps[0] is always 0
    lps[0] = 0;

    // Loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Prints occurrences of pat in txt and returns an array of
// occurrences
int* KMPSearch(const char* pat, const char* txt, int* count)
{
    int M = strlen(pat);
    int N = strlen(txt);

    // Create lps[] that will hold the longest prefix suffix
    // values for pattern
    int* lps = (int*)malloc(M * sizeof(int));

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int* result = (int*)malloc(N * sizeof(int));

    // Number of occurrences found
    *count = 0;

    int i = 0; // index for txt
    int j = 0; // index for pat
  
    while ((N - i) >= (M - j)) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {

            // Record the occurrence (1-based index)
            result[*count] = i - j + 1;
            (*count)++;
            j = lps[j - 1];
        }
        else if (i < N && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i = i + 1;
            }
        }
    }
    free(lps);
    return result;
}

// Driver code
int main()
{
    const char txt[] = "geeksforgeeks";
    const char pat[] = "geeks";
    int count;

    // Call KMPSearch and get the array of occurrences
    int* result = KMPSearch(pat, txt, &count);

    // Print all the occurrences (1-based indices)
    for (int i = 0; i < count; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(result);

    return 0;
}
