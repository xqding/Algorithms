all: main

GCC = g++ -ggdb
main: main.o
	$(GCC) main.o -o main
main.o: main.cpp
	$(GCC) -c main.cpp

rm:
	rm main main.o
