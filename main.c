#include <string.h>
#include <stdlib.h>
#include "file_processing.h"
#include "matrix_operations.h"

// check if first matrix columns equals to second one rows
// check if threads number will exceed 1000
void check_row_column();

int main(int argc, char **argv) {
	// default files paths
	char* input_file_path1 = "a.txt";
	char* input_file_path2 = "b.txt";
	char* output_file_path1 = "c1.out";
	char* output_file_path2 = "c2.out";

	// if user provided files paths rename them
	if (argc == 4) {
		input_file_path1 = argv[1];
		input_file_path2 = argv[2];

		// remove ".out" from output file path
		argv[3] = strtok(argv[3], ".");

		// append 1 & 2 to the output files paths
		output_file_path1 = malloc(strlen(argv[3]) + 1);
		output_file_path2 = malloc(strlen(argv[3]) + 1);
		sprintf(output_file_path1, "%s1.out", argv[3]);
		sprintf(output_file_path2, "%s2.out", argv[3]);
	}

	// open and get input files
	FILE* input1_file = get_file_read(input_file_path1);
	FILE* input2_file = get_file_read(input_file_path2);

	// get columns and rows of the two input matrices
	read_row_col_nums(&row_num1, &col_num1, input1_file);
	read_row_col_nums(&row_num2, &col_num2, input2_file);

	// check conditions
	check_row_column();

	// allocate matrices
	allocate_matrices();

	// read the two input matrices
	read_matrix(row_num1, col_num1, mat_in1, input1_file);
	read_matrix(row_num2, col_num2, mat_in2, input2_file);

	// close input files
	fclose(input1_file);
	fclose(input2_file);

	// then write the matrix to the output file
	// get output file (thread per element method)
	multiply_row_thread();
	FILE* output_file2 = get_file_write(output_file_path2);
	write_matrix(row_num1, col_num2, mat_out, output_file2);

	// then write the matrix to the output file
	// get output file (thread per element method)
	multiply_element_thread();
	FILE* output_file1 = get_file_write(output_file_path1);
	write_matrix(row_num1, col_num2, mat_out, output_file1);

	// free the matrices allocation
	free_matrices();

	// close output files
	fclose(output_file1);
	fclose(output_file2);

	return 0;
}

void check_row_column() {
	if (col_num1 != row_num2) {
		printf("Matrices dimensions are not consistent\n");
		exit(-1);
	}
	if (row_num1 * col_num2 > 10000) {
		printf("Threads will exceed their maximum number of 10000\n");
		exit(-2);
	}
}
