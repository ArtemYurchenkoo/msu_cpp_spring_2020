CC=g++

all: task2

task2: myparser.o test.o
	$(CC) -o parsetest test.o myparser.o

test.o:
	$(CC) -c test.cpp myparser.h

myparser.o:
	$(CC) -c myparser.cpp myparser.h

test: task2
	./parsetest

clean:
	rm -rf *.o task2
