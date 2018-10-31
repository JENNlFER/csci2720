# Makefile to compile, run, and clean code.
# Author - Jennifer Teissler

all: files

run: files
	./main

files:
	g++ -c Main.cpp BinaryTree.cpp ItemType.cpp -Wall -std=c++14 -g -O0
	g++ ItemType.o BinaryTree.o Main.o -o main

clean:
	rm -f main ItemType.o Main.o BinaryTree.o

