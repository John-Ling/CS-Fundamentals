CC := gcc
CFLAGS := -Wall -Werror -Wextra -Wpedantic -I./include -g
LDFLAGS := -L./lib -Wl,-rpath,'$$ORIGIN/../lib'
LDLIBS := -llinkedlist -lutils
OBJ := $(SRC:.c=.o)
BIN := bin/program


linkedlist: 
	$(CC) $(CFLAGS) $(LDFLAGS) -llinkedlist -lutils -o bin/linked_list linked_lists_example.c

skiplist:
	$(CC) $(CFLAGS) $(LDFLAGS)  -llinkedlist -lutils -lskiplist -o bin/skip_list skip_list_example.c


libutils:
	$(CC) $(CFLAGS) -fPIC -c LibUtils/*.c -o LibUtils/utils.o
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -o lib/libutils.so LibUtils/utils.o
	cp LibUtils/*.h include/
	rm LibUtils/utils.o

liblinkedlist:
	$(CC) $(CFLAGS) -fPIC -c LibLinkedList/*.c -o LibLinkedList/linked_list.o
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -o lib/liblinkedlist.so LibLinkedList/linked_list.o
	cp LibLinkedList/*.h include/
	rm LibLinkedList/linked_list.o


libskiplist:
	$(CC) $(CFLAGS) -fPIC -c LibSkipList/*.c -o LibSkipList/skip_list.o
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -o lib/libskiplist.so -llinkedlist -lutils LibSkipList/skip_list.o
	cp LibSkipList/*.h include/
	rm LibSkipList/skip_list.o



.PHONY: clean
clean:
	rm -f $(BIN)


# CC=gcc
# CFLAGS=-Wall -Werror -Wextra -Wpedantic -g
# SRC = main.c array.c data.c 
# OBJ = $(SRC:.c=.o)
 
# # Define the executable name(s)
# EXE = qStud

# # the first target:
# all: driver.o array.o data.o
# 	gcc -o qStud driver.o array.o data.o

# # Other targets specify what .o files rely on
# driver.o: driver.c 
# 	gcc -c driver.c
# array.o: array.c array.h
# 	gcc -c array.c
# data.o: data.c data.h  
# 	gcc -c data.c

# clean:
# 	rm -f *.o qStud 


