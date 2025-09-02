#include "patricia_trie.h"

PatriciaNode* pt_create(char* value)
{
    PatriciaNode* root = _pt_create_node();
    root->value = strdup(value);
    root->prefix = strdup(value);
    root->prefixBitCount = strlen(value) * BITS_PER_BYTE + BITS_PER_BYTE;
    return root;
}

PatriciaNode* _pt_create_node(void)
{
    PatriciaNode* root = (PatriciaNode*)malloc(sizeof(PatriciaNode));
    root->left = NULL;
    root->right = NULL;
    root->value = NULL;
    root->prefix = NULL;
    root->prefixBitCount = 0;
    root->instances = 1;
    return root;
}

PatriciaNode* pt_insert(PatriciaNode* root, char* value, int valueBitCount)
{
    // check if trie is empty 
    // if it is then assign a new terminal / root node
    // then return

    // otherwise
    // iterate through the of prefix until a mismatch is found or prefix runs out of bits

    // if prefix runs out of bits
    // get bit after it and travel left and right respectively
    // then perform the function again using the suffix
    // if no mismatch is found binary matches exactly
    // duplicate node: increase instances by 1
    // check if mismatched bit is 0 or 1 to check left or right child
    // create a new internal node as parent to both inserted value and child

    if (root == NULL) 
    {
        // create node with a full prefix
        PatriciaNode* leaf = _pt_create_node();
        leaf->value = strdup(value);
        leaf->prefix = strdup(value);
        // add extra for null terminator
        leaf->prefixBitCount = strlen(value) * BITS_PER_BYTE + BITS_PER_BYTE; 
        root = leaf;
        return root;
    }


    int mismatchedPosition = -1;
    char* operand = NULL;
    int operandBitCount = 0;
    if (root->prefixBitCount == valueBitCount) 
    {
        mismatchedPosition = _find_bit_mismatch(root->prefix, value, root->prefixBitCount, valueBitCount);
        operand = root->prefix;
        operandBitCount = root->prefixBitCount;
    }
    else
    {
        // if the number of bits don't match the prefix length
        // obivously there is a mismatch
        mismatchedPosition = root->prefixBitCount > valueBitCount ? valueBitCount : root->prefixBitCount;

        // select the shorter length prefix 
        operand = root->prefixBitCount > valueBitCount ? value : root->prefix;
        operandBitCount = root->prefixBitCount > valueBitCount ? valueBitCount : root->prefixBitCount;
    }

    if (mismatchedPosition == -1)
    {
        // no mismatch
        
        // take suffix of search value and travel down either left or right
        // depending on the first bit

        char* suffix = _createStem(value, root->prefixBitCount - 1, 
                            (size_t)(valueBitCount - root->prefixBitCount) / 8);
        
        
        return NULL;
    }

    // mismatch 

    
    // the bit that had a mismatch in the original node
    int mismatchedBit = _getBit(operand, mismatchedPosition);

    int newPrefixBitCount = mismatchedPosition;
    
    // perform splitting operation
    // the current node we are splitting record the prefix and suffix based on the position
    // 

    char* prefix = _createStem(operand, 0, newPrefixBitCount);
    char* suffix = _createStem(operand, mismatchedPosition, operandBitCount - newPrefixBitCount);

    // create an internal node with the binary prefix
    PatriciaNode* internalNode = _pt_create_node();
    internalNode->prefix = prefix;
    internalNode->prefixBitCount = newPrefixBitCount;

    // now create new children

    PatriciaNode* childA = _pt_create_node();
    childA->prefix = suffix;
    childA->prefixBitCount = operandBitCount - newPrefixBitCount;
    childA->value = operand;

    PatriciaNode* childB = _pt_create_node();

    // create prefix for childB
    char* childBSuffix = _createStem(value, mismatchedPosition, operandBitCount - newPrefixBitCount);
    childB->prefix = childBSuffix;
    childB->prefixBitCount = operandBitCount - newPrefixBitCount;
    childB->value = value;

    // attach children
    if (mismatchedBit == 0)
    {
        internalNode->left = childA;
        internalNode->right = childB;
    }
    else
    {
        internalNode->left = childB;
        internalNode->right = childA;
    }
    
    // mismatched bit determine to check left or right child
    // if node has no children

    
    // return the internal node as the root of the subtree 
    return internalNode;
}

int _find_bit_mismatch(char* a, char* b, int bitCountA, int bitCountB)
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
        if (_getBit(a, i) != _getBit(b, i)) 
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

    int isEqual = 1;
    while (isEqual)
    {
        int nullFlagA = 0;
        int nullFlagB = 0;
        for (int i = 0; i < BITS_PER_BYTE; i++)
        {
            // compare bits
            (*totalComparisons)++;
            int bitA = _getBit(a, i);
            int bitB = _getBit(b, i);
            nullFlagA |= bitA;
            nullFlagB |= bitB;

            if (bitA != bitB)
            {
                isEqual = 0;
                break;
            }
        }

        // check if both strings have terminated 
        if ((nullFlagA | nullFlagB))
        {
            break;
        }

        // if only one flag is 0 then one of 
        // our strings terminated early
        // therefore they cannot be the same
        if ((nullFlagA ^ nullFlagB) == 1)
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

int _getBit(char *s, unsigned int bitIndex){
    assert(s && bitIndex >= 0);
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
char* _createStem(char *oldKey, unsigned int startBit, unsigned int numBits){
    assert(numBits > 0 && startBit >= 0 && oldKey);
    int extraBytes = 0;
    if((numBits % BITS_PER_BYTE) > 0){
        extraBytes = 1;
    }
    int totalBytes = (numBits / BITS_PER_BYTE) + extraBytes;
    char *newStem = malloc(sizeof(char) * totalBytes);
    assert(newStem);
    for(unsigned int i = 0; i < totalBytes; i++){
        newStem[i] = 0;
    }
    for(unsigned int i = 0; i < numBits; i++){
        unsigned int indexFromLeft = i % BITS_PER_BYTE;
        unsigned int offset = (BITS_PER_BYTE - indexFromLeft - 1) % BITS_PER_BYTE;
        unsigned int bitMaskForPosition = 1 << offset;
        unsigned int bitValueAtPosition = _getBit(oldKey, startBit + i);
        unsigned int byteInNewStem = i / BITS_PER_BYTE;
        newStem[byteInNewStem] |= bitMaskForPosition * bitValueAtPosition;
    }
    return newStem;
}