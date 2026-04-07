/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** File parser entry point.
*/

#include "./../../include/my_radar.h"

static int error_msg(const char *error)
{
    write(2, error, str_len(error));
    return EXIT_FAIL;
}

// Returning -1 to handle abrupt endings in the middle of a line
static int get_line_size(char *buffer)
{
    int size = 0;

    for (size = 0; buffer[size] && buffer[size] != '\n'; size++);
    return (!buffer[size]) ? -1 : size;
}

static void write_line(char *buffer, char *container, bool *unfinished)
{
    int i = 0;
    int j = 0;

    if ((*unfinished) == true) {
        j = str_len(container);
        (*unfinished) = false;
    }
    for (i = 0; buffer[i] && buffer[i] != '\n'; i++)
        container[i + j] = buffer[i];
    container[i + j] = 0;
}

static int handle_buffer(char *buffer, char *stock,
    bool *unfinished, main_t *main)
{
    int line_size = 0;
    int total = 0;
    int result = 0;

    while (line_size != -1) {
        line_size = get_line_size(buffer);
        total += line_size + 1;
        if (line_size == -1)
            total += str_len(buffer);
        write_line(buffer, stock, unfinished);
        if (total >= PARSER_BUFFER_SIZE && str_len(buffer))
            (*unfinished) = true;
        if ((*unfinished) == false)
            result = parse_single_line(stock, main);
        if (result == EXIT_FAIL)
            return EXIT_FAIL;
        buffer += line_size + 1;
    }
    return EXIT_SUCC;
}

int parser(const char *file_path, main_t *main)
{
    char buffer[PARSER_BUFFER_SIZE] = {0};
    char stock[128] = {0};
    bool unfinished = false;
    size_t total = 1;
    FILE *data = fopen(file_path, "r");

    if (!data)
        return error_msg("File opening failed\n");
    while (total) {
        total = fread(buffer, 1, PARSER_BUFFER_SIZE, data);
        if (!total)
            break;
        buffer[total] = 0;
        if (handle_buffer(buffer, stock, &unfinished, main) == EXIT_FAIL) {
            fclose(data);
            return EXIT_FAIL;
        }
    }
    fclose(data);
    return EXIT_SUCC;
}
