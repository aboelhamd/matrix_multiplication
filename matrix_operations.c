#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include "matrix_operations.h"

// structure to hold parameters to pass to thread
typedef struct s_param {
	int i, j;
} param;

// multiplication process of an element (done by thread)
void* element_mul(void* args) {
	param* params = args;
	int i = params->i, j = params->j;

	int sum_of_mul = 0;
	for (int k = 0; k < row_num2; k++) {
		sum_of_mul += mat_in1[i][k] * mat_in2[k][j];
	}
	mat_out[i][j] = sum_of_mul;

	return NULL;
}

// multiplication process of a row (done by thread)
void* row_mul(void* args) {
	param* params = args;
	int i = params->i;

	for (int j = 0; j < col_num2; j++) {
		int sum_of_mul = 0;
		for (int k = 0; k < row_num2; k++) {
			sum_of_mul += mat_in1[i][k] * mat_in2[k][j];
		}
		mat_out[i][j] = sum_of_mul;
	}

	return NULL;
}
// multiply the two input matrix (by thread per element method)
// then put result in the output matrix
void multiply_element_thread() {
	struct timeval start, stop;
	gettimeofday(&start, NULL);

	pthread_t threads[row_num1 * col_num2];
	int thread_count = 0;

	for (int i = 0; i < row_num1; i++) {
		for (int j = 0; j < col_num2; j++) {
			struct s_param* params = malloc(sizeof(params));
			(*params).i = i;
			(*params).j = j;

			if (pthread_create(&threads[thread_count++], NULL, element_mul,
					(void*) params)) {
				// error
				printf("\nERROR in creating threads\n");
				exit(0);
			}
		}
	}

	for (int i = 0; i < thread_count; i++) {
		pthread_join(threads[i], NULL);
	}

	gettimeofday(&stop, NULL);

	printf(
			"\nThread per element method :\nThreads number is %d\nTime taken in microseconds is %lu\n",
			thread_count, stop.tv_usec - start.tv_usec);
}

// multiply the two input matrix (by thread per row method)
// then put result in the output matrix
void multiply_row_thread() {
	struct timeval start, stop;
	gettimeofday(&start, NULL);

	pthread_t threads[row_num1];
	int thread_count = 0;

	// create threads
	for (int i = 0; i < row_num1; i++) {
		struct s_param* params = malloc(sizeof(params));
		(*params).i = thread_count;
		if (pthread_create(&threads[thread_count++], NULL, row_mul,
				(void*) params)) {
			// error
			printf("\nERROR in creating threads\n");
			exit(0);
		}
	}
	for (int i = 0; i < thread_count; i++) {
		pthread_join(threads[i], NULL);
	}

	gettimeofday(&stop, NULL);

	printf(
			"\nThread per row method :\nThreads number is %d\nTime taken in microseconds is %lu\n",
			thread_count, stop.tv_usec - start.tv_usec);
}

void allocate_matrices() {
	mat_in1 = malloc((size_t) row_num1 * sizeof(int*));
	for (int i = 0; i < row_num1; i++) {
		mat_in1[i] = malloc((size_t) col_num1 * sizeof(int));
	}

	mat_in2 = malloc((size_t) row_num2 * sizeof(int*));
	for (int i = 0; i < row_num2; i++) {
		mat_in2[i] = malloc((size_t) col_num2 * sizeof(int));
	}

	mat_out = malloc((size_t) row_num1 * sizeof(int*));
	for (int i = 0; i < row_num1; i++) {
		mat_out[i] = malloc((size_t) col_num2 * sizeof(int));
	}
}

void free_matrices() {
	free(mat_in1);
	free(mat_in2);
	free(mat_out);
}
