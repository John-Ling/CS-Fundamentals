CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -I./include -g
LDFLAGS := -L./lib -Wl,-rpath,'$$ORIGIN/../lib'
OBJ := $(SRC:.c=.o)
BIN := bin/program


linkedlist: 
	$(CC) $(CFLAGS) $(LDFLAGS) -llinkedlist -lutils -o bin/linked_list linked_lists_example.c

skiplist:
	$(CC) $(CFLAGS) $(LDFLAGS)  -llinkedlist -lutils -lskiplist -o bin/skip_list skip_list_example.c

queue:
	$(CC) $(CFLAGS) $(LDFLAGS)  -llinkedlist -lutils -lqueue -o bin/queues queues_example.c

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

.PHONY: clean
clean:
	rm -f $(BIN)