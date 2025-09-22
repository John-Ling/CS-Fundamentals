#include "markov_text_generation.h"

int main(int argc, char* argv[]) 
{
    
    int order = atoi(argv[1]);
    int generationLength = atoi(argv[2]); // length to generate in words
    char* src = argv[3];

    create_transition_matrix(src, order);
    return EXIT_SUCCESS;
}

HashTable* create_transition_matrix(char* filename, int order)
{
    FILE* src = fopen(filename, "r");
    fseek(src, 0, SEEK_END);
    long size = ftell(src);
    rewind(src);
    char buffer[size + 1];
    buffer[size] = '\0';

    size_t bytesRead = fread(buffer, 1, size, src);
    if (bytesRead != size) 
    {
        fclose(src);
        return NULL;
    }

    fclose(src);

    // tokenize file contents 
    char** tokens = (char**)malloc(sizeof(char*) * 50);
    int allocated = 50;
    int tokenCount = 0;
    int i = 0; 

    const char *delimiters = " \t\n";
    char* token = strtok(buffer, delimiters);
    while (token != NULL) 
    {
        tokens[i] = strdup(token);
        i++;
        tokenCount++;
        token = strtok(NULL, delimiters);

        if (token != NULL)
        {
            allocated += 50;
            tokens = (char**)realloc(tokens, sizeof(char*)  * allocated);
        }
    }

    printf("%d\n", tokenCount);
    printf("%s\n", tokens[0]);

    HashTable* table = LibHashTable.create(STRING, 15, sizeof(double)) ;

    // go through and collect bigrams via sliding window 
    int front = 2;
    int back = 0;
    int center = 1;

    // collect bigrams
    while (front < tokenCount) 
    {
        char* current = tokens[center];
        char* previous = tokens[back];
        char* next = tokens[front];


        char* bigram = strcat(previous, current);

        LibHashTable.insert_str(table, bigram, 1);
        front++;
        back++;
        center++;
    }



    

    
    return table;

}