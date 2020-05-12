CC = g++

all: test

test: test.o
	$(CC) -o test test.o --std=c++17 -pthread
	./test

test.o:
	$(CC) -c test.cpp thread_sort.h ThreadPool.h --std=c++17 -pthread

clean:
	rm -rf *.o test
	rm -rf *.h.gch
	rm test_input
	rm test_output