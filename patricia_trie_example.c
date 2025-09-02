#include <stdio.h>
#include <stdlib.h>
#include "patricia_trie.h"


int main(void)
{
    // printf("%s\n", _createStem("asdf", 8, 2 * BITS_PER_BYTE));

    int mismatchedPosition = 6;

    char* stemA = _createStem("a",0, 4);
    char* stemB = _createStem("b",0, 5);

    // int ret = bitwiseStrcmp(stemA, stemB, &mismatchedPosition);
    

    // if (ret == 1)
    // {
    //     printf("Matching strings\n");
    // }
    // else
    // {
    //     printf("Strings mismatched at %d\n", mismatchedPosition);
    // }


    PatriciaNode* root = pt_create("a");
    printf("%d\n", root->prefixBitCount);


    // tests for bit mismatch function
    // printf("%d\n", _find_bit_mismatch(stemA, stemB, 4, 5));        
    // printf("%d\n", _find_bit_mismatch(stemA, stemB, 4, 5));

    root = pt_insert(root, "b", 8 + 8);



    

    // printf("%d\n", _find_bit_mismatch(a, b));
    return EXIT_SUCCESS;
}