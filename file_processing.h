#ifndef FILE_PROCESSING_H_
#define FILE_PROCESSING_H_
#include <stdio.h>

// Open the given file for reading and return it
FILE* get_file_read(char* file_path);
// Open the given file for writing and return it
FILE* get_file_write(char* file_path);

// write a line to the given file
void write_line_to_file(FILE* file, char* line);

// read a line from the given file
void read_line_from_file(FILE* file, char line[512]);

// read row and column values in first line of the given file and put them in the given pointers
void read_row_col_nums(int* row, int* col, FILE* file);

// read matrix from the given file an put it in the given 2D array pointer
void read_matrix(int row, int col, int** matrix, FILE* file);

// read line (row of matrix) from the given file and put it in the given array pointer
void read_row(int* row[], FILE* file);

// write the given matrix to the given file
void write_matrix(int row, int col, int** matrix, FILE* file);

#endif /* FILE_PROCESSING_H_ */
