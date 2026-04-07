/*
** EPITECH PROJECT, 2025
** c_alloc
** File description:
** Function to calloc based on malloc.
*/

#include <stdlib.h>

void *c_alloc(const size_t element_count, const size_t element_size)
{
    char *alloc = malloc(element_size * element_count);

    if (!alloc)
        return NULL;
    for (size_t i = 0; i < element_count * element_size; i++)
        alloc[i] = 0;
    return (void *)alloc;
}
