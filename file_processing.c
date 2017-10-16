#include <stdio.h>
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

char* read_line_from_file(FILE* file) {
	char line[512];
	if (fgets(line, 512, file)) {
		// remove the '\n' from the line
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
	}
	return line;
}

void read_row_col_nums(int* row, int* col, FILE* file) {

}

void read_matrix(int* matrix[][], FILE* file) {

}

void read_row(int* row[], FILE* file) {

}

void write_matrix(int matrix[][], FILE* file) {

}
