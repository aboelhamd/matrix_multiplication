#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include "matrix_operations.h"

// struct to hold parameters to pass to thread
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
	mat_out1[i][j] = sum_of_mul;

	return NULL;
}

// multiplication process of a row (done by thread)
void* row_mul(void* args) {
	int* i = args;

	for (int j = 0; j < col_num2; j++) {
		int sum_of_mul = 0;
		for (int k = 0; k < row_num2; k++) {
			sum_of_mul += mat_in1[*i][k] * mat_in2[k][j];
		}
		mat_out1[*i][j] = sum_of_mul;
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
			struct s_param params;
			params.i = i;
			params.j = j;

			if (!pthread_create(&threads[thread_count], NULL, element_mul,
					&params)) {
				pthread_join(threads[thread_count], NULL);
			} else {
				// error
				printf("ERROR\n");
			}

			thread_count++;
		}
	}

	gettimeofday(&stop, NULL);

	printf(
			"Thread per element method :\nThreads number is %d\nTime taken in microseconds is %lu\n",
			thread_count, stop.tv_usec - stop.tv_usec);
}

// multiply the two input matrix (by thread per row method)
// then put result in the output matrix
void multiply_row_thread() {
	struct timeval start, stop;
	gettimeofday(&start, NULL);

	pthread_t threads[row_num1];
	int thread_count = 0;

	for (int i = 0; i < row_num1; i++) {
		if (!pthread_create(&threads[thread_count], NULL, element_mul, &i)) {
			pthread_join(threads[thread_count], NULL);
		} else {
			// error
			printf("ERROR\n");
		}

		thread_count++;
	}

	gettimeofday(&stop, NULL);

	printf(
			"Thread per row method :\nThreads number is %d\nTime taken in microseconds is %lu\n",
			thread_count, stop.tv_usec - stop.tv_usec);
}
