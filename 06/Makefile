CC=g++

all: task6

task6: test

test1.o:
	$(CC) -c test1.cpp format.h

test1: test1.o
	$(CC) -o test1 test1.o format.h

test: test1.o test1
	./test1

clean:
	rm -rf *.h.gch task6
	rm -rf *.o task6