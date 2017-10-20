#compiler variable
CC=gcc
#flag compile variable
CFLAGS=-c 

LIBFLAG=-lpthread

all : matmult.out

matmult.out : main.o file_processing.o matrix_operations.o
	$(CC) main.o file_processing.o matrix_operations.o -o matmult.out $(LIBFLAG)

main.o : main.c file_processing.h matrix_operations.h
	$(CC) $(CFLAGS) main.c

file_processing.o : file_processing.c file_processing.h
	$(CC) $(CFLAGS) file_processing.c

matrix_operations.o : matrix_operations.c matrix_operations.h
	$(CC) $(CFLAGS) matrix_operations.c

clean : 
	rm -rf *o matmult.out