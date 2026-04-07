/*
** EPITECH PROJECT, 2025
** multiple_free
** File description:
** Function to safely free multiple memory blocks at once.
*/

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

static int str_len(const char *str)
{
    int i = 0;

    for (i = 0; str[i]; i++);
    return i;
}

static int error_msg(const char *error)
{
    write(2, error, str_len(error));
    return 84;
}

static int protected_free(void **block)
{
    if (!block || !(*block))
        return error_msg("Attempted to free a wrong pointer!\n");
    free(*block);
    *block = ((void *)0);
    return 0;
}

// Must pass the address of the pointer you are attempting to free!
int safe_free(int n, ...)
{
    va_list blocks;

    va_start(blocks, n);
    for (int i = 0; i < n; i++) {
        if (protected_free(va_arg(blocks, void **)) == 84)
            return 84;
    }
    return 0;
}
