CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g

all: tail

# Sestaveni vyslednych programu
tail: tail.c
	$(CC) $(CFLAGS) tail.c -o tail

clean:
	rm *.o tail 

zip:
	zip xbockaa.zip *.c *.cc *.h Makefile