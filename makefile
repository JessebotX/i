CC = cc
CFLAGS = -std=c89 -pedantic -Og

SRC = main.c
EXE = main

all:
	$(CC) $(CFLAGS) $(SRC) -o $(EXE)
