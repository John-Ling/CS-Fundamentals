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

    printf("Creating Markov Model" "\n");
    
    HashTable* model = create_markov_model(src, order); 
    printf("Generating:""\n");
    sleep(2);
    generate_text(model, wordCount);

    LibHashTable.free(model, _free_markov_state);
    return EXIT_SUCCESS;
}

// tokenise contents of a file then insert them into a 
// markov model represented using a hash table
HashTable* create_markov_model(char* filename, int order)
{
    HashTable* model = LibHashTable.create(STRING, 15, sizeof(MarkovState));
    size_t tokenCount = 0;
    char** tokens = _generate_tokens(filename, &tokenCount);
    _generate_ngrams(model, (const char**)tokens, tokenCount, order);

    for (int i = 0; i < tokenCount; i++)
    {
        free(tokens[i]);
        tokens[i] = NULL;
    }
    free(tokens);
    tokens = NULL;
    return model;
}

char** _generate_tokens(char* filename, size_t* _tokenCount) 
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

    const char *delimiters = " \t\n\"-";
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
    (*_tokenCount) = tokenCount;
    free(buffer);
    buffer = NULL;
    return tokens;
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
        
        char* current = tokens[i];
        char* next = tokens[i + 1];
        size_t ngramLength = strlen(current) + 1; // add 1 for null terminator

        for (int j = order; j >= 1; j--)
        {
            char* previous = tokens[i - j];
            ngramLength += strlen(previous) + 1; // add 1 for the space
        }

        char ngram[ngramLength];
        ngram[0] = '\0';

        for (int j = order; j >= 1; j--)
        {
            strcat(ngram, tokens[i - j]);
            strcat(ngram, " ");
        }

        strcat(ngram, current);
        ngramCount++;
        
        // ether update or insert ngram
        KeyValue* pair = LibHashTable.get_str(model, ngram);
        
        if (pair == NULL)
        {
            MarkovState state;
            state.ngram = strdup(ngram);
            state.nextWords = LibLinkedList.create(NULL, 0, sizeof(NextWord));
            NextWord nextWord;
            nextWord.word = strdup(next);
            nextWord.probability = 1; 
            LibLinkedList.insert(state.nextWords, (void*)&nextWord, -1);
            LibHashTable.insert_str(model, ngram, (void*)&state);
        }
        else
        {
            MarkovState* state = (MarkovState*)pair->data;
            NextWord nextWord;
            nextWord.word = strdup(next);
            nextWord.probability = 1; 

            // check if next already exists in linked list 
            NextWord* searchResult = (NextWord*)LibLinkedList.search(
                                                state->nextWords, 
                                                (void*)&nextWord,
                                                 _compare_next_word_structs);

            if (searchResult != NULL)
            {
                state->nextWords->itemCount++;
                searchResult->probability++;
                free(nextWord.word);
                nextWord.word = NULL;
            }
            else
            {
                LibLinkedList.insert(state->nextWords, (void*)&nextWord, -1);
            }
        }   
    }
    // normalise probabilities 
    _normalise_probabilities(model);
    LibHashTable.print_keys(model, _print_markov_state);
    return ngramCount;
}

// go through model and normalise the probabilities by dividing
// them by the ngramCount
int _normalise_probabilities(HashTable* model)
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
                nextWord->probability /= nextWords->itemCount;
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
    char* startNgram = _get_starter(model);
    printf("%s ", startNgram);
    char* currentNgram = startNgram;
    while (1)
    {
        // printf("Current ngram %s\n", currentNgram);
        if (generatedCount > wordCount)
        {
            break;
        }
        
        KeyValue* pair = LibHashTable.get_str(model, currentNgram);
        if (pair == NULL)
        {
            // find new starting ngram
            // add code later 
            currentNgram = _get_starter(model); // for now use fixed ngram 
            pair = LibHashTable.get_str(model, currentNgram);
        }
        
        char* next = _select_next_word(((MarkovState*)pair->data)->nextWords);
        printf("%s ", next);

        // form new ngram
        // take last word in ngram
        char* lastSpace = strrchr(currentNgram, ' ');
        char* lastWord;
        lastWord = lastSpace == NULL ? currentNgram : lastSpace + 1;

        int newNgramLength  = strlen(lastWord) + strlen(next) + 1;
        // form new ngram
        char newNgram[newNgramLength];
        newNgram[0] = '\0';
        strcat(newNgram, lastWord);
        strcat(newNgram, " ");
        strcat(newNgram, next);
        currentNgram = newNgram;
        generatedCount++;

        fflush(stdout); 
        usleep(50000);
        
    }
    return EXIT_SUCCESS;
}

char* _select_next_word(LinkedList* possibleWords)
{
    double chance = (double)rand() / RAND_MAX;
    double cumulative = 0;

    ListNode* current = possibleWords->head; 
    while (current != NULL)
    {
        NextWord* word = (NextWord*)current->value;
        cumulative += word->probability;
        if (cumulative >= chance)
        {
            return word->word;
        }
        current = current->next;
    }

    // if we end up here somehow run again
    return _select_next_word(possibleWords);
}

// returns a random ngram from the model
// that begins with a capital letter
char* _get_starter(HashTable* model)
{
    LinkedList* bucket = NULL;
    do 
    {
        bucket = model->buckets[rand() % model->bucketCount];
    }
    while (bucket->head == NULL);
    
    int bucketPosition = rand() % bucket->itemCount;

    ListNode* current = bucket->head;

    for (int i = 0; i < bucketPosition; i++) 
    {
        current = current->next;
    }

    MarkovState* state = (MarkovState*)((KeyValue*)current->value)->data;
    return state->ngram;
}

void _free_markov_state(void* d)
{
    MarkovState* state = (MarkovState*)d;
    LibLinkedList.free(state->nextWords, _free_next_word_struct);
    free(state->ngram);
    state->ngram = NULL;
    free(state);
    state = NULL;
    return;
}

void _free_next_word_struct(void* d)
{
    NextWord* nextWord = (NextWord*)d;
    free(nextWord->word);
    nextWord->word = NULL;
    free(nextWord);
    nextWord = NULL;
    return;
}

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
    printf("%s | ", state->ngram);
    LibLinkedList.print(state->nextWords, _print_next_word_struct);
    return;
}

void _print_next_word_struct(const void* d)
{
    NextWord* nextWord = (NextWord*)d;
    printf("%s %.2lf ", nextWord->word, nextWord->probability);
    return;
}