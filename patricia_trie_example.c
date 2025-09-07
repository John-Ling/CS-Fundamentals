#include <stdio.h>
#include <stdlib.h>
#include "patricia_trie.h"


int main(void)
{
    PatriciaNode* root = pt_create("a");
    for (char i = 'a'; i <= 'z'; i++)
    {
        char* c = &i;
        root = pt_insert(root, c, 8 + 8);
    }

    pt_free(root);

    // test with multi char keys
    root = pt_create("dog");
    root = pt_insert(root, "doggo", strlen("doggo") * 8 + 8);
    root = pt_insert(root, "doge", strlen("doge") * 8 + 8);
    root = pt_insert(root, "doggone", strlen("doggone") * 8 + 8);
    pt_free(root);
    return EXIT_SUCCESS;
}