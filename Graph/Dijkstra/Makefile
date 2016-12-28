CC = g++

main: main.o 
	$(CC) main.o -o main
main.o: main.cpp Heap.h Heap.inl
	$(CC) -c main.cpp
clean:
	rm main.o Heap.o

# main: main.o Heap.o
# 	$(CC) main.o Heap.o -o main
# main.o: main.cpp
# 	$(CC) -c main.cpp
# Heap.o: Heap.cpp Heap.h
# 	$(CC) -c Heap.cpp
# clean:
# 	rm main.o Heap.o
