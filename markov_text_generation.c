#include "markov_text_generation.h"

// implementation details
// build the markov chain

// functionality 
// select a random (valid) starting word
// from there look at the possible candidates for the next one
// generate a value randomly from 0 and 1 and pick the candidate with the closest probability
// 

// todo reimplement with potentially more efficient radix/patricia trie

void print_key_str(const void* data)
{
    KeyValue* pair = (KeyValue*)data;
    printf("%s %f ", (char*)pair->key, *(double*)pair->data);
    return;
}

void print_markov_state(const void* data)
{
    if (data == NULL)
    {
        puts("Data is NULL");
        return;
    }

    KeyValue* pair = (KeyValue*)data;
    MarkovState* state = (MarkovState*)pair->data;

    printf("NGRAM: %s\n", pair->key);
    LibHashTable.print_keys(state->possibles, print_key_str);
    return;
}

int main(int argc, char* argv[]) 
{
    srand(time(NULL));
    int order = atoi(argv[1]);
    int wordCount = atoi(argv[2]); // length to generate in words
    char* src = argv[3];

    HashTable* model = create_markov_model(src, order);

    // generate text using transition matrix

    return EXIT_SUCCESS;
}

// tokenise contents of a file then insert them into a 
// markov model represented using a hash table
HashTable* create_markov_model(char* filename, int order)
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
    size_t tokenCount = 0;

    const char *delimiters = " \t\n";
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

    HashTable* model = LibHashTable.create(STRING, 15, sizeof(MarkovState));

    _generate_ngrams(model, (const char**)tokens, tokenCount, order);
    free(tokens);
    tokens = NULL;
    return model;
}

// populates the markov model with ngrams collected from tokens
// returns the number of ngrams generated from a collection of tokens
int _generate_ngrams(HashTable* model, const char** tokens, size_t tokenCount, int order)
{
    double ngramCount = 0;

    // collect ngrams
    for (int i = 0; i < tokenCount - 1; i++)
    {
        if (i - order < 0)
        {
            continue; 
        }

        char* ngram = NULL;
        char* current = tokens[i];
        char* next = tokens[i + 1];
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
        ngramCount++;

        KeyValue* pair = LibHashTable.get_str(model, ngram);
        
        if (pair == NULL)
        {
            // ngram does not exist in the table
            MarkovState* state = _create_markov_state();
            double a = 1;
            LibHashTable.insert_str(state->possibles, next, &a);
            LibHashTable.insert_str(model, ngram, (void*)state);
            assert(state->possibles->buckets != NULL);
        }
        else
        {
            MarkovState* state = (MarkovState*)pair->data;
            KeyValue* _pair = LibHashTable.get_str(state->possibles, next);
            double newValue = 1;
            if (_pair != NULL)
            {
                // word exists in the possibles so update probability
                newValue = (*(double*)_pair->data + 1);
            }
            LibHashTable.insert_str(state->possibles, next, &newValue);
            assert(state->possibles->buckets != NULL);
        }    

        free(ngram);
        ngram = NULL;
    }

    // why is possibles becoming null fix this bug
    for (int i = 0; i < model->bucketCount; i++)
    {
        assert(((MarkovState*)model->buckets[i]->head->value)->possibles->buckets != NULL);
    }
    // normalise probabilities 
    // puts("Running");
    _normalise_probabilities(model, ngramCount);
    // puts("Done");
    LibHashTable.print_keys(model, print_markov_state);
    return ngramCount;
}

// go through model and normalise the probabilities by dividing
// them by the ngramCount
int _normalise_probabilities(HashTable* model, int ngramCount)
{
    for (int i = 0; i < model->bucketCount; i++)
    {
        if (model->buckets[i]->head == NULL)
        {
            continue;
        }

        // recall the model is a hash table mapping strings to MarkovStates
        MarkovState* current = (MarkovState*)model->buckets[i]->head->value;
        HashTable* candidates = current->possibles;
        assert(candidates->buckets != NULL);
        for (int j = 0; j < candidates->bucketCount; j++) 
        {
            if (candidates->buckets[j]->head == NULL) 
            {
                continue;
            }

            // each Markov state contains a hash table mapping strings to doubles
            // ListNode* currentNode = current->possibles->buckets[j]->head;
            // while (currentNode != NULL) 
            // {
            //     KeyValue* pair = (KeyValue*)currentNode->value;
            //     double newValue = *(double*)pair->data / ngramCount;
            //     // pair->data = &newValue;
            //     currentNode = currentNode->next;
            // }
        }       
    }
    return EXIT_SUCCESS;
}

int generate_text(HashTable* model, int wordCount)
{
    int generatedCount = 1;

    // for now use a fixed starting ngram
    char* startNgram = "didn't think";

    // while (1)
    // {
    //     // 
    //     // pick 
    //     if (generatedCount > wordCount && )
    // }

}

// returns a random ngram from the model
// that begins with a capital letter
// char* get_starter(HashTable* model)
// {
//     // pick a random item from the 
//     return 
// }

MarkovState* _create_markov_state(void)
{
    MarkovState* state = (MarkovState*)malloc(sizeof(MarkovState));
    state->possibles = LibHashTable.create(STRING, 5, sizeof(double));
    return state;
}