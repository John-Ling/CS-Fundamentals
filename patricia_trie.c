#include "patricia_trie.h"

PatriciaNode* pt_create(const char* value)
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

    PatriciaNode *parent = NULL, *grandparent = NULL;
    PatriciaNode* leaf = pt_search(root, &parent, &grandparent, value);

    if (strcmp(leaf->value, value) == 0) {
        // duplicate
        return root;
    }

    int mismatch = _find_bit_mismatch(leaf->value, value, leaf->prefixBitCount, valueBitCount);
    PatriciaNode* newLeaf = pt_create(value);
    PatriciaNode* internal = malloc(sizeof(PatriciaNode));
    internal->mismatchIndex = mismatch;
    internal->value = NULL;
    internal->prefixBitCount = 0;

    

    // attach leaves based on mismatched bit
    if (_get_bit(value, mismatch) == 0) {
        internal->left = newLeaf;
        internal->right = leaf;
    } else {
        internal->left = leaf;
        internal->right = newLeaf;
    }

    // find parent to attach internal node
    if (!parent) {
        // new internal becomes root
        return internal;
    }

    if (_get_bit(value, parent->mismatchIndex) == 0) {
        parent->left = internal;
    } else {
        parent->right = internal;
    }

    return root;
}

PatriciaNode* pt_search(PatriciaNode* root, PatriciaNode** parent, PatriciaNode** grandparent, 
                        const char* value)
{
    printf("Searching for %s\n", value);
    (*grandparent) = NULL;
    // if root is a leaf node check immediately 

    if (root->mismatchIndex == -1 && strcmp(root->value, value) == 0) 
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
        printf("Got bit %d at %d\n ", _get_bit(value, current->mismatchIndex), current->mismatchIndex);
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

PatriciaNode* pt_search_by_key(PatriciaNode* root, const char* key) 
{
    PatriciaNode* parent;
    PatriciaNode* grandparent;
    return pt_search(root, &parent, &grandparent, key);
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

    int minBits = bitCountA < bitCountB ? bitCountA : bitCountB;

    for (int i = 0; i < minBits; i++) {
        if (_get_bit(a, i) != _get_bit(b, i)) {
            return i; // first mismatching bit
        }
    }

    // all overlapping bits match, but lengths differ
    if (bitCountA != bitCountB) {
        return minBits;
    }

    return -1; // identical
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