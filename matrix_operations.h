#ifndef MATRIX_OPERATIONS_H_
#define MATRIX_OPERATIONS_H_

int **mat_in1, **mat_in2, **mat_out;
int row_num1, row_num2, col_num1, col_num2;

// multiply the two input matrix (by thread per element method)
// then put result in the output matrix
void multiply_element_thread();

// multiply the two input matrix (by thread per row method)
// then put result in the output matrix
void multiply_row_thread();

// allocate memory of the 3 matrices
void allocate_matrices();

// free memory of the 3 matrices
void free_matrices();

#endif /* MATRIX_OPERATIONS_H_ */
