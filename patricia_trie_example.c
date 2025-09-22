#include <stdio.h>
#include <stdlib.h>
#include "patricia_trie.h"


int main(void)
{
    PatriciaNode* root = pt_create("a");
    char* c = (char*)malloc(sizeof(char));
    for (char i = 'a'; i <= 'z'; i++)
    {
        c[0] = i;
        root = pt_insert(root, c, 8 + 8);
    }
    ;


    for (char i = 'a'; i <= 'z'; i++) 
    {
        c[0] = i;
        PatriciaNode* found = pt_search_by_key(root, c);
        printf("%s\n", found->value);
    }

    free(c);
    c = NULL;

    pt_free(root);

    // test with multi char keys
    root = pt_create("dog");
    root = pt_insert(root, "doggo", strlen("doggo") * 8 + 8);
    root = pt_insert(root, "doge", strlen("doge") * 8 + 8);
    root = pt_insert(root, "doggone", strlen("doggone") * 8 + 8);
    root = pt_insert(root, "wagwan", strlen("wagwan") * 8 + 8);

    PatriciaNode* found  = pt_search_by_key(root, "doge");
    printf("%s\n", found->value);
    found = pt_search_by_key(root, "dog");
    printf("%s\n", found->value);
    found = pt_search_by_key(root, "doggo");
    printf("%s\n", found->value);
    found = pt_search_by_key(root, "doggone");
    printf("%s\n", found->value);
    found = pt_search_by_key(root, "wagwan");
    found = pt_search_by_key(root, "a");
    found = pt_search_by_key(root, "");
    printf("%s\n", found->value);
    
    pt_free(root);

    


    // return EXIT_SUCCESS;
}