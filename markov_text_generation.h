#ifndef Markov_Text_Generation_H
#define Markov_Text_Generation_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "hash_table.h"


// typedef struct MarkovState_t
// {
//     HashTable* possibles;
// } MarkovState;

typedef struct NextWord_t 
{
    char* word;
    double frequency;   
} NextWord;

typedef struct MarkovState_t
{
    char* ngram;
    LinkedList* nextWords; // linked lists of potential next words
} MarkovState;

int main(int argc, char* argv[]);
HashTable* create_markov_model(char* filename, int order);
int _generate_ngrams(HashTable* model, const char** tokens, size_t tokenCount, int order);
int _normalise_probabilities(HashTable* model, int ngramCount);
MarkovState* _create_markov_state(void);
int _compare_next_word_structs(const void* a, const void* b);
void _print_next_word_struct(const void* d);
void _print_markov_state(const void* d);
#endif 