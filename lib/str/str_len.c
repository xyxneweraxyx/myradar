/*
** EPITECH PROJECT, 2025
** str_len
** File description:
** Function to get the length of a string.
*/

int str_len(const char *str)
{
    int i = 0;

    for (i = 0; str[i]; i++);
    return i;
}
