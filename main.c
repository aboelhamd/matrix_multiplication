#include <string.h>
#include <stdlib.h>
#include "file_processing.h"

// do all the job , change its name later
void do_it_all(int argc, char **argv);

// multiply the two input matrix and put result in the output matrix
void multiply(int row1, int col1, int row2, int col2, int matrix1[row1][col1],
		int matrix2[row2][col2], int matrix[row1][col2]);

int main(int argc, char **argv) {
//	do_it_all(argc, argv);

	return 0;
}

void multiply(int row1, int col1, int row2, int col2, int matrix1[row1][col1],
		int matrix2[row2][col2], int matrix[row1][col2]) {

}

void do_it_all(int argc, char **argv) {
	// default files paths
	char* input1_file_path = "a.txt";
	char* input2_file_path = "b.txt";
	char* output_file_path = "c.out";

	// if user provided files paths rename them
	if (argc == 4) {
		input1_file_path = argv[1];
		input2_file_path = argv[2];
		output_file_path = argv[3];
	}

	// open and get input files
	FILE* input1_file = get_file(input1_file_path);
	FILE* input2_file = get_file(input2_file_path);

	// get columns and rows of the two input matrices
	int row1, col1, row2, col2;
	read_row_col_nums(&row1, &col1, input1_file);
	read_row_col_nums(&row2, &col2, input2_file);

	// get the two matrices
	int matrix1[row1][col1];
	int matrix2[row2][col2];
	read_matrix(row1, col1, matrix1, input1_file);
	read_matrix(row2, col2, matrix2, input2_file);

	// close input files
	fclose(input1_file);
	fclose(input2_file);

	// get output matrix
	int matrix[row1][col2];
	multiply(row1, row2, col1, col2, matrix1, matrix2, matrix);

	// write the matrix to the output file
	write_matrix(row1, col2, matrix, output_file_path);

}
