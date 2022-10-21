#include <stdlib.h>
#include "Buffer.h"
#include "Sort_functions.h"
#include "Comparators.h"

enum
{
    MAIN_ARGUMENTS_ERR,
    READ_FILE_ERR,
    EMPTY_FILE_ERR,
    CREATE_BUFFER_ERR,
    CREATE_ARR_OF_STRUCTURES_ERR,
    CREATE_OUTPUT_FILE_ERR,
};

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Enter the name of a file you want to sort\n");
        return MAIN_ARGUMENTS_ERR;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == nullptr)
    {
        printf("Failed to read a file\n");
        return READ_FILE_ERR;
    }

    size_t file_size = get_file_size(file);
    if (!file_size)
    {
        printf("The file is empty\n");
        fclose(file);
        return EMPTY_FILE_ERR;
    }

    char* buffer = read_file_to_buffer(file, file_size);
    if (buffer == nullptr)
    {
        printf("Failed to create a buffer\n");
        fclose(file);
        return CREATE_BUFFER_ERR;
    }

    fclose(file);

    size_t number_of_lines = count_lines(buffer);

    change_delimiter(buffer, '\n', '\0');

    Line* arr_of_structures = split_buffer(buffer, number_of_lines, file_size);
    if (arr_of_structures == nullptr)
    {
        printf("Failed to create an array of structures\n");
        free(buffer);
        return CREATE_ARR_OF_STRUCTURES_ERR;
    }

    FILE* output_file = fopen("Output.txt", "w+");
    if (output_file == nullptr)
    {
        printf("Failed to create an output file\n");
        free(buffer);
        free(arr_of_structures);
        return CREATE_OUTPUT_FILE_ERR;
    }

    qsort (arr_of_structures, number_of_lines, sizeof(*arr_of_structures), straight_cmp_from_beginning);
    output(arr_of_structures, number_of_lines, output_file);

    qsort(arr_of_structures, number_of_lines, sizeof(*arr_of_structures), reverse_cmp_from_beginning  );
    output(arr_of_structures, number_of_lines, output_file);

    qsort(arr_of_structures, number_of_lines, sizeof(*arr_of_structures), straight_cmp_from_end       );
    output(arr_of_structures, number_of_lines, output_file);

    qsort(arr_of_structures, number_of_lines, sizeof(*arr_of_structures), reverse_cmp_from_end        );
    output(arr_of_structures, number_of_lines, output_file);

    output_original(buffer, number_of_lines, output_file);

    fclose(output_file);
}