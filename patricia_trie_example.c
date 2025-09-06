#include <stdio.h>
#include <stdlib.h>
#include "patricia_trie.h"


int main(void)
{
    PatriciaNode* root = pt_create("dog");
    printf("%d\n", root->prefixBitCount);


    // tests for bit mismatch function
    // printf("%d\n", _find_bit_mismatch(stemA, stemB, 4, 5));        
    // printf("%d\n", _find_bit_mismatch(stemA, stemB, 4, 5));

    // root = pt_insert(root, "dog", strlen("dog") * 8 + 8);
    root = pt_insert(root, "doggo", strlen("doggo") * 8 + 8);
    root = pt_insert(root, "doge", strlen("doge") * 8 + 8);
    // root = pt_insert(root, "doggone", strlen("doggone") * 8 + 8);
    // printf("%d\n", _find_bit_mismatch(a, b));
    return EXIT_SUCCESS;
}