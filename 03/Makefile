CC=g++

all: task3

task3: testmatrix

testmatrix.o:
	$(CC) -c testmatrix.cpp matrix.h

matrix.o:
	$(CC) -c matrix.cpp matrix.h

testmatrix: matrix.o testmatrix.o
	$(CC) -o testmatrix testmatrix.o matrix.o

test: task3
	./testmatrix

clean:
	rm -rf *.o task3