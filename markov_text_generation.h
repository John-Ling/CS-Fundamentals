#ifndef Markov_Text_Generation_H
#define Markov_Text_Generation_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

int main(int argc, char* argv[]);
HashTable* create_transition_matrix(char* filename, int order);
#endif 