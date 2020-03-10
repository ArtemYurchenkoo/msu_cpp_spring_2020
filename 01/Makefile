CC=g++

all: task1

task1: allocator.o test_alloc_once.o test_two_allocs.o test_reset.o test_alloc_size_control.o
	$(CC) -o test_alloc_once test_alloc_once.o allocator.o
	$(CC) -o test_two_allocs test_two_allocs.o allocator.o
	$(CC) -o test_reset test_reset.o allocator.o
	$(CC) -o test_alloc_size_control test_alloc_size_control.o allocator.o

test_alloc_once.o:
	$(CC) -c test_alloc_once.cpp allocator.h

test_deny_access.o:
	$(CC) -c test_two_allocs.cpp allocator.h

test_reset.o:
	$(CC) -c test_reset.cpp allocator.h

allocator.o:
	$(CC) -c allocator.cpp allocator.h

test_alloc_size_control.o:
	$(CC) -c test_alloc_size_control.cpp allocator.h

test_alloc_once:
	./test_alloc_once

test_two_allocs:
	./test_two_allocs

test_reset:
	./test_reset

test_alloc:
	./test_alloc_size_control

test: 
	./test_alloc_once
	./test_two_allocs
	./test_reset
	./test_alloc_size_control

clean:
	rm -rf *.o task1
