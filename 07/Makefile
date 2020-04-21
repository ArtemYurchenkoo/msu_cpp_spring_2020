CC=g++

all: test

test: test.o vector.h
	$(CC) -o test test.cpp
	./test

clean:
	-rm test test.o 
	-rm -rf *.h.gch