CC = cc
CFLAGS = -std=c89 -pedantic -Wall -Og

SRC = main.c
EXE = main

all:
	$(CC) $(CFLAGS) $(SRC) -o $(EXE)
