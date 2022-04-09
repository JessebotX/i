CC = cc
CC_WIN = gcc
CFLAGS = -std=c89 -pedantic -Og

SRC = main.c
EXE = ssg

all:
	$(CC) $(CFLAGS) $(SRC) -o $(EXE)

windows:
	$(CC_WIN) $(CFLAGS) $(SRC) -o $(EXE)
