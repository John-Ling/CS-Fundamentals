#include "markov_text_generation.h"

// implementation details
// build the markov chain

// functionality 
// select a random (valid) starting word
// from there look at the possible nextWords for the next one
// generate a value randomly from 0 and 1 and pick the candidate with the closest probability
// 

// todo reimplement with potentially more efficient radix/patricia trie

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

        // ether update or insert ngram
        KeyValue* pair = LibHashTable.get_str(model, ngram);
        
        if (pair == NULL)
        {
            puts("Inserting new");
            // ngram does not exist in the table
            MarkovState* state = _create_markov_state();
            double a = 1;

            state->ngram = strdup(ngram);
            if (state->ngram == NULL)
            {
                puts("MEMORY ERROR");
            }

            NextWord* nextWord = (NextWord*)malloc(sizeof(NextWord));
            nextWord->word = strdup(next);
            nextWord->frequency = 1; 

            printf("%s %lf\n", nextWord->word, nextWord->frequency);

            // state->nextWords 
            LibLinkedList.insert(state->nextWords, (void*)nextWord, -1);
            LibLinkedList.print(state->nextWords, _print_next_word_struct);
            LibHashTable.insert_str(model, ngram, (void*)state);
            pair = LibHashTable.get_str(model, ngram);
            
            puts("Retriving");
            if (pair != NULL)
            {
                puts("Found");
                MarkovState* s = (MarkovState*)pair->data;
                
                LibLinkedList.print(s->nextWords, _print_next_word_struct);
                printf("%s\n", s->ngram);
            }
        }
        else
        {
            MarkovState* state = (MarkovState*)pair->data;
            NextWord* nextWord = (NextWord*)malloc(sizeof(NextWord));
            nextWord->word = strdup(next);
            nextWord->frequency = 1; 
            // check if next already exists in linked list 
            NextWord* searchResult = (NextWord*)LibLinkedList.search(
                                                state->nextWords, 
                                                (void*)nextWord,
                                                 _compare_next_word_structs);
            if (searchResult != NULL)
            {
                puts("UPdating");
                // update search result
                searchResult->frequency++;
            }
            else
            {
                puts("Not FOund");
                LibLinkedList.insert(state->nextWords, (void*)nextWord, -1);
            }

            pair = LibHashTable.get_str(model, ngram);
            
            puts("Retriving");
            if (pair != NULL)
            {
                puts("Found");
                MarkovState* s = (MarkovState*)pair->data;
                
                LibLinkedList.print(s->nextWords, _print_next_word_struct);
                printf("%s\n", s->ngram);
            }
        }   
        
        free(ngram);
        ngram = NULL;
    }

    // why does this work
    // but not direct access

    // index 4
    // KeyValue* pair = LibHashTable.get_str(model, "nor his");
    // puts("Retriving");
    // if (pair != NULL)
    // {
    //     puts("Found");
    //     MarkovState* s = (MarkovState*)pair->data;
    //     ListNode* current = s->nextWords->head;
    //     while (current != NULL)
    //     {
    //         NextWord* nextWord = (NextWord*)current->value;
    //         printf("%s ", nextWord->word);
    //         current = current->next;
    //     }
    // }


    // printf("\n%s\n", ((MarkovState*)((KeyValue*)model->buckets[4]->head->value)->data)->ngram);
    // try direct retrieval 
    // NextWord* nextword = ((MarkovState*)model->buckets[0]->head)->nextWords->head->value;
    // printf("\n%s\n", nextword->word);

    // normalise probabilities 
    _normalise_probabilities(model, ngramCount);
    
// 
    LibHashTable.print_keys(model, _print_markov_state);
    // puts("Done");
    return ngramCount;
}

// go through model and normalise the probabilities by dividing
// them by the ngramCount
int _normalise_probabilities(HashTable* model, int ngramCount)
{
    for (int i = 0; i < model->bucketCount; i++)
    {
        LinkedList* bucket = model->buckets[i];
        if (bucket->head == NULL)
        {
            continue;
        }

        ListNode* current = bucket->head;
        while (current != NULL)
        {
            KeyValue* pair = (KeyValue*)current->value;
            MarkovState* state = (MarkovState*)pair->data;
            LinkedList* nextWords = state->nextWords;

            // offending line has a random address
            // not null but still problematic
            ListNode* currentWord = nextWords->head;
            while (currentWord != NULL)
            {
                // line that causes the segfault
                // trying to access memory in a inproper location
                NextWord* nextWord = (NextWord*)currentWord->value;
                nextWord->frequency /= ngramCount;
                currentWord = currentWord->next;
            }
            current = current->next;
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
    state->nextWords = LibLinkedList.create(NULL, 0, sizeof(NextWord));

    return state;
}

int _compare_next_word_structs(const void* a, const void* b)
{
    NextWord* c = (NextWord*)a;
    NextWord* d = (NextWord*)b;
    
    if (strcmp(c->word, d->word) == 0)
    {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

void _print_markov_state(const void* d)
{
    KeyValue* pair = (KeyValue*)d;
    MarkovState* state = (MarkovState*)pair->data;
    printf("%s ", state->ngram);
    LibLinkedList.print(state->nextWords, _print_next_word_struct);
    return;
}

void _print_next_word_struct(const void* d)
{
    NextWord* nextWord = (NextWord*)d;
    printf("%s %lf ", nextWord->word, nextWord->frequency);
    return;
}