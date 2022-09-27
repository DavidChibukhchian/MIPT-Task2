#include <stdio.h>
#include <sys\stat.h>
#include <assert.h>
#include "Buffer.h"

size_t get_file_size(FILE* filename)
{
    assert(filename != nullptr);

    struct stat file_data{};
    fstat(fileno(filename), &file_data);
    return file_data.st_size;

#if 0
    assert(filename != nullptr);

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    return size;
#endif
}

char* read_file_to_buffer(FILE* filename, size_t filesize)
{
    assert(filename != nullptr);
    assert(filesize != 0);

    char* buffer = (char*) calloc(1 + filesize + 1, sizeof(char));
    if (buffer == nullptr)
    {
        return nullptr;
    }

    * buffer                            = '\n';
    *(buffer + filesize + sizeof(char)) = '\0';

    fread(buffer + sizeof(char), sizeof (char), filesize, filename);
    fclose(filename);

    return buffer;
}

size_t count_lines(char* buffer)
{
    assert(buffer != nullptr);

    size_t number_of_lines = 0;

    buffer++;
    while (*buffer != '\0')
    {
        if ((*(buffer - sizeof(char)) == '\n') && (*buffer != '\n'))
        {
            number_of_lines++;
        }
        buffer++;
    }
    return number_of_lines;
}

void delete_slash_n (char* buffer)
{
    assert(buffer != nullptr);

    while (*buffer != '\0')
    {
        if (*buffer == '\n')
        {
            *buffer = '\0';
        }
        buffer++;
    }
}

Line* split_buffer(char* buffer, size_t number_of_lines, size_t file_size)
{
    assert(buffer           !=  nullptr);
    assert(number_of_lines  !=     0   );
    assert(file_size        !=     0   );

    Line* arr_of_structures = (Line*) calloc(number_of_lines, sizeof(Line));
    if (arr_of_structures == nullptr) {return nullptr;}

    buffer++;
    Line* arr_of_structures_i = arr_of_structures;

    for (size_t i = 0; i <= file_size; i++)
    {
        if ( (*(buffer + i - 1) == '\0') && (*(buffer + i) != '\0') )
        {
            arr_of_structures_i->line_ptr =        buffer + i;
            arr_of_structures_i->length   = strlen(buffer + i);
            arr_of_structures_i++;
        }
    }
    return arr_of_structures;
}

void output(Line* arr_of_structures, size_t number_of_lines, FILE* output_file)
{
    assert(arr_of_structures != nullptr);
    assert(number_of_lines   !=    0   );
    assert(output_file       != nullptr);

    for (size_t i = 0; i < number_of_lines; i++)
    {
        fputs((arr_of_structures + i)->line_ptr, output_file);
        fputs("\n", output_file);
    }
    fputs("\n\n\n", output_file);
}

void output_original(char* buffer, size_t number_of_lines, FILE* output_file)
{
    assert(buffer          != nullptr);
    assert(number_of_lines !=    0   );
    assert(output_file     != nullptr);

    buffer++;
    for (size_t i = 0; i < number_of_lines; i++)
    {
        fputs(buffer, output_file);
        fputs("\n", output_file);

        while(*buffer != '\0')
        {
            buffer++;
        }
        while(*buffer == '\0')
        {
            buffer++;
        }
    }
}
