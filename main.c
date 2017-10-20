#include <string.h>
#include <stdlib.h>
#include "file_processing.h"
#include "matrix_operations.h"

int main(int argc, char **argv) {
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
	read_row_col_nums(&row_num1, &col_num1, input1_file);
	read_row_col_nums(&row_num2, &col_num2, input2_file);

	// get the two matrices
	mat_in1 = malloc((size_t) row_num1 * sizeof(int*));
	for (int i = 0; i < row_num1; i++) {
		mat_in1[i] = malloc((size_t) col_num1 * sizeof(int));
	}
	read_matrix(row_num1, col_num1, mat_in1, input1_file);

	mat_in2 = malloc((size_t) row_num2 * sizeof(int*));
	for (int i = 0; i < row_num2; i++) {
		mat_in2[i] = malloc((size_t) col_num2 * sizeof(int));
	}
	read_matrix(row_num2, col_num2, mat_in2, input2_file);

	// get output matrix
	mat_out1 = malloc((size_t) row_num1 * sizeof(int*));
	for (int i = 0; i < row_num1; i++) {
		mat_out1[i] = malloc((size_t) col_num2 * sizeof(int));
	}
	multiply_element_thread();
	multiply_row_thread();

	// get output file then write the matrix to the output file
	FILE* output_file = get_file(output_file_path);
	write_matrix(row_num1, col_num2, mat_out1, output_file);

	return 0;
}
