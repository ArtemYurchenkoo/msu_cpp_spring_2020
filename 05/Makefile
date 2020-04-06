CC=g++

all: task5

task5: test

test1.o: bigint.o
	$(CC) -c test1.cpp

test1: test1.o bigint.o
	$(CC) -o test1 test1.o bigint.o

bigint.o:
	$(CC) -c bigint.cpp bigint.h

test: test1.o bigint.o test1
	./test1

clean:
	rm -rf *.h.gch task5
	rm -rf *.o task5