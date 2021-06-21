# William Diebolt (cssc2128), Frank Gomez (cssc2151)
# CS570, Summer 2020
# Assignment 2
# Makefile


EXEC = msh
CC = gcc
$(EXEC):
	$(CC) -std=c99 -o $(EXEC) main.c msh.c
	rm -f *.o
clean:
	rm -f $(EXEC)
