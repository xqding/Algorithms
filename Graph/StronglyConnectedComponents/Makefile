all: main

GCC = g++ -ggdb
main: main.o DFS.o
	$(GCC) main.o DFS.o -o main
main.o: main.cpp
	$(GCC) -c main.cpp
DFS.o: DFS.h DFS.cpp
	$(GCC) -c DFS.cpp

rm:
	rm main main.o
