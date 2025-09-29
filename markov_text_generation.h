#ifndef Markov_Text_Generation_H
#define Markov_Text_Generation_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h> 
#include <time.h>
#include "hash_table.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define BAR "=========================================================="

// typedef struct MarkovState_t
// {
//     HashTable* possibles;
// } MarkovState;

typedef struct NextWord_t 
{
    char* word;
    double probability;   
} NextWord;

typedef struct MarkovState_t
{
    char* ngram;
    LinkedList* nextWords; // linked lists of potential next words
} MarkovState;

int main(int argc, char* argv[]);
HashTable* create_markov_model(char* filename, int order);
int generate_text(HashTable* model, int wordCount);
char** _generate_tokens(char* filename, size_t* _tokenCount);
int _generate_ngrams(HashTable* model, const char** tokens, size_t tokenCount, int order);
int _normalise_probabilities(HashTable* model);
char* _select_next_word(LinkedList* possibleWords);
char* _get_starter(HashTable* model);
MarkovState* _create_markov_state(void);
int _compare_next_word_structs(const void* a, const void* b);
void _print_next_word_struct(const void* d);
void _print_markov_state(const void* d);
void _free_next_word_struct(void* d);
void _free_markov_state(void* d);
#endif 