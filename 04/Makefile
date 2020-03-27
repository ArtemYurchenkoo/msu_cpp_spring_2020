CC=g++

all: task4

task4: test

test1.o:
	$(CC) -c test1.cpp serializer.h

test1: test1.o
	$(CC) -o test1 test1.o serializer.h

test: test1.o test1
	./test1

clean:
	rm -rf *.h.gch task4
	rm -rf *.o task4