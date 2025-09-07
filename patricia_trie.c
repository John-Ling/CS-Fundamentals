#include "patricia_trie.h"

PatriciaNode* pt_create(char* value)
{
    PatriciaNode* root = _pt_create_node();
    root->value = strdup(value);
    root->mismatchIndex = -1;
    root->prefixBitCount = strlen(value) * BITS_PER_BYTE + BITS_PER_BYTE;
    root->left = root;
    root->right = root;
    return root;
}

PatriciaNode* pt_insert(PatriciaNode* root, const char* value, int valueBitCount)
{
    if (root == NULL) 
    {
        PatriciaNode* node = _pt_create_node();
        node->value = strdup(value);
        node->prefixBitCount = valueBitCount;
        node->mismatchIndex = -1; // leaf sentinel
        node->left = node->right = node; // points to self (Patricia leaf convention)
        return node;
    }

    PatriciaNode* foundGrandparent = NULL;
    PatriciaNode* foundParent = NULL;
    // search for existing key
    PatriciaNode* found = pt_search(root, &foundParent, &foundGrandparent, value);

    if (found && strcmp(found->value, value) == 0) 
    {
        puts("Found duplicate node");
        return root; 
    }

    // find mismatching index
    int mismatchIndex = _find_bit_mismatch(found->value, value, found->prefixBitCount, valueBitCount);    
    if (mismatchIndex == -1)
    {
        // mismatch index shouldn't be -1
        puts("Walao sum ting wong");
        return NULL;
    }

    // create leaf node
    PatriciaNode* leaf = _pt_create_node();
    leaf->value = strdup(value);
    leaf->prefixBitCount = valueBitCount;

    // create internal node 
    PatriciaNode* internal = _pt_create_node();
    internal->mismatchIndex = mismatchIndex;

    int mismatchedBit = _get_bit(value, mismatchIndex);


    if (foundParent == NULL)
    {
        switch (mismatchedBit)
        {
            case 0:
                internal->left = leaf;
                internal->right = found;
                break;
            case 1:
                internal->left = found;
                internal->right = leaf;
                break;
        }
        return internal;
    }

    if (mismatchIndex < foundParent->mismatchIndex)
    {
        // if the found parent is null then we must only possess a single node
        // in the trie
        // make the internal node as our new root
        
        switch (mismatchedBit)
        {
            case 0:
                internal->left = leaf;
                internal->right = foundParent;
                break;
            case 1:
                internal->left = foundParent;
                internal->right = leaf;
                break;
        }

        if (foundGrandparent == NULL)
        {
            root = internal;
        }
        else if (foundGrandparent->left == foundParent)
        {
            foundGrandparent->left = internal;
        }
        else
        {
            foundGrandparent->right = internal;
        }

        return root;
    }

    // mismatch index is longer than the parent's
    // attach the internal node to the parent's left or right
    switch (mismatchedBit)
    {
        case 0:
            internal->left = leaf;
            internal->right = found;
            foundParent->left = internal;
            break;
        case 1:
            internal->left = found;
            internal->right = leaf;
            foundParent->right = internal;
            break;
    }

    return root;
}

PatriciaNode* pt_search(PatriciaNode* root, PatriciaNode** parent, PatriciaNode** grandparent, 
                        const char* value)
{
    (*grandparent) = NULL;
    // if root is a leaf node check immediately 
    if (root->mismatchIndex == -1 && strcmp(root->value, value) == EXIT_SUCCESS) 
    {
        (*parent) = NULL;
        return root;
    }



    PatriciaNode* current = root;
    // this statement checks if we have reached a leaf node
    // try changing to check if mismatch index == -1 since we 
    // assume this is a leaf node
    while (current->mismatchIndex != -1) 
    {
        (*grandparent) = (*parent);
        (*parent) = current;
        switch(_get_bit(value, current->mismatchIndex))
        {
            case 0:
                current = current->left;
                break;
            case 1:
                current = current->right;
                break;
        }
    }
    return current;
}

void pt_free(PatriciaNode* root)
{
    if (root->mismatchIndex == -1)
    {
        // free root node
        free(root->value);
        root->value = NULL;
        free(root);
        root = NULL;
        return;
    }

    pt_free(root->left);
    pt_free(root->right);

    // free internal node
    free(root);
    return;
}


PatriciaNode* _pt_create_node(void)
{
    PatriciaNode* root = (PatriciaNode*)malloc(sizeof(PatriciaNode));
    root->value = NULL;
    root->prefixBitCount = 0;
    root->mismatchIndex = -1;
    root->instances = 1;
    root->left = root;
    root->right = root;
    return root;
}

int _find_bit_mismatch(const char* a, const char* b, int bitCountA, int bitCountB)
{
    // takes in two strings
    // it's not guaranteed that these strings will
    // be null terminated
    // so bit lengths for each string are required

    // returns a 0-indexed value for the mismatching bit
    // returns -1 if no mismatch was found

    if (bitCountA != bitCountB)
    {
        // if bit counts mismatch we assume the mismatching bit to the bit index
        // immediately after the truncated string
        // aka the shorter string's length
        return bitCountA > bitCountB ? bitCountB : bitCountA;
    }

    for (int i = 0; i < bitCountA; i++)
    {
        if (_get_bit(a, i) != _get_bit(b, i)) 
        {
            return i;    
        }
    }

    return -1;
}

int _get_bit(const char *s, unsigned int bitIndex)
{
    assert(s && (int)bitIndex >= 0);
    unsigned int byte = bitIndex / BITS_PER_BYTE;
    unsigned int indexFromLeft = bitIndex % BITS_PER_BYTE;
    /* 
        Since we split from the highest order bit first, the bit we are interested
        will be the highest order bit, rather than a bit that occurs at the end of the
        number. 
    */
    unsigned int offset = (BITS_PER_BYTE - (indexFromLeft) - 1) % BITS_PER_BYTE;
    unsigned char byteOfInterest = s[byte];
    unsigned int offsetMask = (1 << offset);
    unsigned int maskedByte = (byteOfInterest & offsetMask);
    /*
        The masked byte will still have the bit in its original position, to return
        either 0 or 1, we need to move the bit to the lowest order bit in the number.
    */
    unsigned int bitOnly = maskedByte >> offset;
    return bitOnly;
}