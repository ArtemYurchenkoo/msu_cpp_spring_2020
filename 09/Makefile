CC = g++

all: test

sort.o:
	$(CC) -c thread_sort.cpp --std=c++17 -pthread
test: test.o sort.o
	$(CC) -o test test.o thread_sort.o --std=c++17 -pthread
	./test

test.o:
	$(CC) -c test.cpp --std=c++17 -pthread

clean:
	rm -rf *.o test
	rm test_input
	rm test_output
	rm chunk*