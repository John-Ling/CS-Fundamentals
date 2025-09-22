#include "markov_text_generation.h"

void print_key_str(const void* data)
{
    if (data == NULL)
    {
        puts("Data is NULL");
        return;
    }
    KeyValue* pair = (KeyValue*)data;

    printf("%s ", (char*)pair->key);
    return;
}


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
    char* buffer = malloc(sizeof(char) * (size + 1));
    buffer[size] = '\0';

    long bytesRead = fread(buffer, 1, size, src);
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

    const char *delimiters = " \t\n()";
    char* token = strtok(buffer, delimiters);
    while (token != NULL) 
    {
        if (tokenCount >= allocated)
        {
            allocated += 50;
            tokens = (char**)realloc(tokens, sizeof(char*)  * allocated);
        }

        tokens[tokenCount] = strdup(token);
        tokenCount++;
        token = strtok(NULL, delimiters);
    }


    HashTable* table = LibHashTable.create(STRING, 15, sizeof(double)) ;

    int ngramCount = 0;
    // collect ngrams
    for (int i = 0; i < tokenCount; i++)
    {
        if (i - order < 0)
        {
            continue; 
        }

        char* ngram = NULL;
        char* current = tokens[i];
        size_t ngramLength = strlen(current) + 1; // add 1 for null terminator

        for (int j = order; j >= 1; j--)
        {
            char* previous = tokens[i - j];
            ngramLength += strlen(previous) + 1; // add 1 for the space
        }

        ngram = (char*)malloc(sizeof(char) * ngramLength);
        ngram[0] = '\0';

        for (int j = order; j >= 1; j--)
        {
            strcat(ngram, tokens[i - j]);
            strcat(ngram, " ");
        }

        strcat(ngram, current);
        printf("%s\n", ngram);

        puts("Searching");
        KeyValue* pair = LibHashTable.get_str(table, ngram);

        puts("Search  complete");
        if (pair == NULL)
        {
            double a = 1;
            LibHashTable.insert_str(table, ngram, &a);
        }
        else
        {
            double newValue = *(double*)pair->data + 1;
            LibHashTable.insert_str(table, ngram, &newValue);
        }    
    }

    LibHashTable.print_keys(table, print_key_str);

    KeyValue* pair = LibHashTable.get_str(table, "Mister DJ");
    if (pair == NULL)
    {
        printf("Null\n");
    }
    else
    {
        printf("%f\n", *(double*)pair->data);
    }
    

    free(tokens);
    tokens = NULL;
    return table;
}