LN=ld
CC=gcc

HEADERS=bigint/bigd.h bigint/bigdigits.h bigint.h list.h hashtab.h io.h net.h stack.h tree.h type.h
SOURCES=bigint/bigd.c bigint/bigdigits.c bigint.c list.c hashtab.c io.c net.c stack.c tree.c type.c
OBJECTS=bigint.o list.o hashtab.o io.o net.o stack.o tree.o type.o

.PHONY: default compile link clean
default: compile link
compile: $(SOURCES) $(HEADERS)
	$(CC) bigint/bigd.c -c -o bigint/bigd.o
	$(CC) bigint/bigdigits.c -c -o bigint/bigdigits.o
	$(CC) bigint.c -c -o bigint/bigint.o
	$(LN) -r bigint/bigd.o bigint/bigdigits.o bigint/bigint.o -o bigint.o
	$(CC) -c list.c hashtab.c io.c net.c stack.c tree.c type.c
link:
	$(LN) -r $(OBJECTS) -o extclib.o
clean:
	rm -f *.o 
