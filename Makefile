CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -I./include -g
LDFLAGS := -L./lib -Wl,-rpath,'$$ORIGIN/../lib'
OBJ := $(SRC:.c=.o)
BIN := bin/*

linkedlist: 
	$(CC) $(CFLAGS) $(LDFLAGS) -llinkedlist -lutils -o bin/linked_list linked_lists_example.c

skiplist:
	$(CC) $(CFLAGS) $(LDFLAGS)  -llinkedlist -lutils -lskiplist -o bin/skip_list skip_list_example.c

queue:
	$(CC) $(CFLAGS) $(LDFLAGS)  -llinkedlist -lutils -lqueue -o bin/queues queues_example.c

quicksort:
	$(CC) $(CFLAGS) $(LDFLAGS)-lutils -o bin/quicksort quicksort.c

hashtable:
	$(CC) $(CFLAGS) $(LDFLAGS)  -llinkedlist -lutils  -lhashtable -o bin/hash_table hash_table_example.c

bloomfilter:
	$(CC) $(CFLAGS) $(LDFLAGS) -lbloomfilter -lm -o bin/bloom_filter bloom_filter_example.c

markov:
	$(CC) $(CFLAGS) $(LDFLAGS) -lhashtable -llinkedlist  -lutils -o bin/markov_text_generation markov_text_generation.c

libutils:
	$(CC) $(CFLAGS) -fPIC -c LibUtils/*.c -o LibUtils/utils.o
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -o lib/libutils.so LibUtils/utils.o
	rm LibUtils/utils.o

liblinkedlist:
	$(CC) $(CFLAGS) -fPIC -c LibLinkedList/*.c -o LibLinkedList/linked_list.o
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -o lib/liblinkedlist.so LibLinkedList/linked_list.o
	rm LibLinkedList/linked_list.o

libskiplist:
	$(CC) $(CFLAGS) -fPIC -c LibSkipList/*.c -o LibSkipList/skip_list.o
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -o lib/libskiplist.so -llinkedlist -lutils LibSkipList/skip_list.o
	rm LibSkipList/skip_list.o

libqueue:
	$(CC) $(CFLAGS) -fPIC -c LibQueue/*.c -o LibQueue/queue.o
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -o lib/libqueue.so -llinkedlist -lutils LibQueue/queue.o
	rm LibQueue/queue.o

libhashtable:
	$(CC) $(CFLAGS) -fPIC -c LibHashTable/*.c -o LibHashTable/hash_table.o
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -o lib/libhashtable.so -llinkedlist -lutils LibHashTable/hash_table.o
	rm LibHashTable/hash_table.o

libbloomfilter:
	$(CC) $(CFLAGS) -fPIC -c LibBloomFilter/*.c -o LibBloomFilter/bloom_filter.o
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -o lib/libbloomfilter.so -lm LibBloomFilter/bloom_filter.o
	rm LibBloomFilter/bloom_filter.o

.PHONY: clean
clean:
	rm -f $(BIN)