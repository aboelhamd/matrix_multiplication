#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_processing.h"

FILE* get_file(char* file_path) {
	// open file or create it if not found
	return fopen(file_path, "a+");
}

void write_line_to_file(FILE* file, char* line) {
	// put line
	fputs(line, file);
	fputs("\n", file);
}

void read_line_from_file(FILE* file, char line[512]) {
	if (fgets(line, 512, file)) {
		// remove the '\n' from the line
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
	}
}

void read_row_col_nums(int* row, int* col, FILE* file) {
	// read the line "row=x col=y"
	char line[512];
	read_line_from_file(file, line);

	// get row and column numbers by removing all non-number chars
	// then convert string into integers
	char* num = strtok(line, "rowcl= \t");
	*row = strtol(num, &num, 10);

	num = strtok(NULL, "rowcl= \t");
	*col = strtol(num, &num, 10);
}

void read_matrix(int row_num, int col_num, int** matrix, FILE* file) {
	char line[512];

	// read the corresponding row
	for (int i = 0; i < row_num; i++) {
		read_line_from_file(file, line);
		char*row = line;
//		printf("%d  %d\n", i, row_num);

		// extract the corresponding column and saves it in the matrix
		for (int j = 0; j < col_num; j++) {
			matrix[i][j] = strtol(row, &row, 10);
//			printf("%d ", matrix[i][j]);
		}
//		printf("\n");
	}
}

void write_matrix(int row_num, int col_num, int** matrix, FILE* file) {
	char* line = malloc(512);

	for (int i = 0; i < row_num; i++) {
		memset(line, 0, 512);

		// put each number one by one in the line
		for (int j = 0; j < col_num; j++) {
			sprintf(line, "%s %d", line, matrix[i][j]);
		}

		// write the line to the file
		write_line_to_file(file, line);
	}
	free(line);
}
