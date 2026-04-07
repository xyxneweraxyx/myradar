/*
** EPITECH PROJECT, 2025
** str_to_int
** File description:
** Function to attempt conversion from a string to an int.
*/

#include <stdio.h>

int str_to_int(const char *str)
{
    int total = 0;
    int i = 0;

    for (i = 0; str[i] && str[i] >= '0' && str[i] <= '9'; i++)
        total = total * 10 + (str[i] - '0');
    return ((str[i] >= '0' && str[i] <= '9') || !str[i]) ? total : -1;
}
