#include "patricia_trie.h"

PatriciaNode* pt_create(char* value)
{
    PatriciaNode* root = _pt_create_node();
    root->value = value;
    root->prefix = value;
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

    PatriciaNode* foundParent = NULL;
    // search for existing key
    PatriciaNode* found = pt_search(root, &foundParent, value);

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

    if (foundParent == NULL ||  mismatchIndex < foundParent->mismatchIndex)
    {
        // if the found parent is null then we must only possess a single node
        // in the trie
        // make the internal node as our new root

        if (foundParent == NULL)
        {
            foundParent = found;
        }

        switch(mismatchedBit)
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

        return internal;
    }

    // mismatch index is longer than the parent's
    // attach the internal node to the parent's left or right
    switch(mismatchedBit)
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

PatriciaNode* pt_search(PatriciaNode* root, PatriciaNode** parent, const char* value)
{
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


PatriciaNode* _pt_create_node(void)
{
    PatriciaNode* root = (PatriciaNode*)malloc(sizeof(PatriciaNode));
    root->value = NULL;
    root->prefix = NULL;
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

int _bitwiseStrcmp(char* a, char*  b, int* totalComparisons)
{
    // Return 1 if two strings are equal
    // Returns 0 otherwise
    // counts number of bitwise comparisons
    // assumes a and b are null terminated strings

    _Bool isEqual = 1;
    while (isEqual)
    {
        _Bool nullFlagA = 0;
        _Bool nullFlagB = 0;
        for (int i = 0; i < BITS_PER_BYTE; i++)
        {
            // compare bits
            (*totalComparisons)++;
            _Bool bitA = _get_bit(a, i);
            _Bool bitB = _get_bit(b, i);
            nullFlagA |= bitA;
            nullFlagB |= bitB;

            if (bitA != bitB)
            {
                isEqual = 0;
                break;
            }
        }

        // check if both strings have terminated 
        if (nullFlagA | nullFlagB)
        {
            break;
        }

        // if only one flag is 0 then one of 
        // our strings terminated early
        // therefore they cannot be the same
        if (nullFlagA ^ nullFlagB)
        {
            isEqual = 0;
            break;
        }

        a++;
        b++;
    }

    return isEqual;
}


/* Returns min of 3 integers 
    reference: https://www.geeksforgeeks.org/edit-distance-in-c/ */
int _min(int a, int b, int c) {
    if (a < b) {
        if(a < c) {
            return a;
        } else {
            return c;
        }
    } else {
        if(b < c) {
            return b;
        } else {
            return c;
        }
    }
}

/* Returns the edit distance of two strings
    reference: https://www.geeksforgeeks.org/edit-distance-in-c/ */
int _editDistance(char *str1, char *str2, int n, int m){
    assert(m >= 0 && n >= 0 && (str1 || m == 0) && (str2 || n == 0));
    // Declare a 2D array to store the dynamic programming
    // table
    int dp[n + 1][m + 1];

    // Initialize the dp table
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            // If the first string is empty, the only option
            // is to insert all characters of the second
            // string
            if (i == 0) {
                dp[i][j] = j;
            }
            // If the second string is empty, the only
            // option is to remove all characters of the
            // first string
            else if (j == 0) {
                dp[i][j] = i;
            }
            // If the last characters are the same, no
            // modification is necessary to the string.
            else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = _min(1 + dp[i - 1][j], 1 + dp[i][j - 1],
                    dp[i - 1][j - 1]);
            }
            else {
                // If the last characters are different,
                // consider all three operations and find the
                // minimum
                dp[i][j] = 1 + _min(dp[i - 1][j], dp[i][j - 1],
                    dp[i - 1][j - 1]);
            }
        }
    }

    // Return the result from the dynamic programming table
    return dp[n][m];
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

/* Allocates new memory to hold the numBits specified and fills the allocated
    memory with the numBits specified starting from the startBit of the oldKey
    array of bytes. */
char* _createStem(const char *oldKey, unsigned int startBit, unsigned int numBits){
    assert((int)numBits > 0 && (int)startBit >= 0 && oldKey);
    int extraBytes = 0;
    if((numBits % BITS_PER_BYTE) > 0){
        extraBytes = 1;
    }
    unsigned int totalBytes = (numBits / BITS_PER_BYTE) + extraBytes;
    char *newStem = malloc(sizeof(char) * totalBytes);
    assert(newStem);
    for(unsigned int i = 0; i < totalBytes; i++){
        newStem[i] = 0;
    }
    for(unsigned int i = 0; i < numBits; i++){
        unsigned int indexFromLeft = i % BITS_PER_BYTE;
        unsigned int offset = (BITS_PER_BYTE - indexFromLeft - 1) % BITS_PER_BYTE;
        unsigned int bitMaskForPosition = 1 << offset;
        unsigned int bitValueAtPosition = _get_bit(oldKey, startBit + i);
        unsigned int byteInNewStem = i / BITS_PER_BYTE;
        newStem[byteInNewStem] |= bitMaskForPosition * bitValueAtPosition;
    }
    return newStem;
}