# Makefile to compile, run, and clean code.
# Author - Jennifer Teissler

all: files

run: files
	./main

files:
	g++ -c Main.cpp SortedLinkedList.cpp DataType.cpp -Wall -std=c++14 -g -O0
	g++ DataType.o SortedLinkedList.o Main.o -o main

clean:
	rm -f main DataType.o Main.o SortedLinkedList.o

