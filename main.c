#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "file_processing.h"

int** mat_in1;
int** mat_in2;
int** mat_out;

// do all the job , change its name later
void do_it_all(int argc, char **argv);

// multiply the two input matrix and put result in the output matrix
void multiply(int row1, int common_dim, int col2, int matrix1[row1][common_dim],
		int matrix2[common_dim][col2], int matrix[row1][col2]);

void element_mul(int row1, int common_dim, int col2,
		int matrix1[row1][common_dim], int matrix2[common_dim][col2],
		int matrix[row1][col2]);

typedef struct s_params {
	int row1, common_dim, col2, i, j;
	int** matrix1; //, matrix2[], matrix[][];
} params;

int main(int argc, char **argv) {
////	do_it_all(argc, argv);
//
//	params p;
//
//	int mat[2][3] = { 1, 2, 3, 4, 5, 6 };
//
//	p.matrix1 = malloc(2 * sizeof(int*));
//
//	for (int i = 0; i < 2; i++)
//		p.matrix1[i] = malloc(3 * sizeof(int));
//
////	p.matrix1 = mat;
//
//	p.matrix1[0][0] = 5;

	mat_in1 = malloc(2);
	for (int i = 0; i < 2; i++)
		mat_in1[i] = malloc(3);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			mat_in1[i][j] = 5;
			printf("%d  ", mat_in1[i][j]);
		}
		printf("\n");
	}

	return 0;
}

//xyzzy plugh;
//plugh.num = 42;
//strcpy (plugh.name, "paxdiablo");
//plugh.secret = 3.141592653589;

void multiply(int row1, int common_dim, int col2, int matrix1[row1][common_dim],
		int matrix2[common_dim][col2], int matrix[row1][col2]) {
	for (int i = 0; i < row1; i++) {
		// from here , threads of one row
		for (int j = 0; j < col2; j++) {
			// from here , threads of one element
			pthread_t elem_thread;
//			int thread_status = pthread_create(&elem_thread, NULL, element_mul,
//			NULL);

		}
	}
}

//void element_mul(int row1, int common_dim, int col2,
//		int matrix1[row1][common_dim], int matrix2[common_dim][col2],
//		int matrix[row1][col2], int i, int j) {
//
//	int sum_of_mul = 0;
//	for (int k = 0; k < common_dim; k++) {
//		sum_of_mul += matrix1[i][k] * matrix2[k][j];
//	}
//	matrix[i][j] = sum_of_mul;
//}

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

// get output matrix
	int matrix[row1][col2];
	multiply(row1, row2, col2, matrix1, matrix2, matrix);

// get output file then write the matrix to the output file
	FILE* output_file = get_file(output_file_path);
	write_matrix(row1, col2, matrix, output_file);

}
