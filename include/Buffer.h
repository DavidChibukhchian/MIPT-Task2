#ifndef TASK2_BUFFER_H
#define TASK2_BUFFER_H
#include <stdio.h>

size_t get_file_size(FILE* filename);

char* read_file_to_buffer(FILE* filename, size_t filesize);

size_t count_lines(char* buffer);

void delete_slash_n(char* buffer);

struct Line
{
    char* line_ptr;
    size_t length;
};

Line* split_buffer(char* buffer, size_t number_of_lines, size_t size);

void output (Line* arr_of_structures, size_t number_of_lines, FILE* output_file);

void output_original   (char* buffer, size_t number_of_lines, FILE* output_file);

#endif //TASK2_BUFFER_H
