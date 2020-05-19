LAB = Lab6
CC = gcc
.PHONY: all build run clean valgrind splint

all: $(LAB)

clean: 
	@rm -rf $(LAB) *.o *.exe *.out

build: $(LAB)

$(LAB): $(LAB).o
	$(CC) -o $(LAB) $(LAB).o

$(LAB).o: $(LAB).c
	$(CC) -c $(LAB).c -std=c89

run: 
	./$(LAB)

valgrind: a.out
	valgrind --leak-check=full -v ./$(LAB).exe

a.out: $(LAB).c
	$(CC) -g $(LAB).c

splint:
	splint $(LAB).c
