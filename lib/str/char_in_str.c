/*
** EPITECH PROJECT, 2025
** str_str
** File description:
** Function to try and find a char in a string. Returns position if found.
*/

int char_in_str(char c, const char *str)
{
    int i = 0;

    for (i = 0; str[i] && str[i] != c; i++);
    return (str[i] == c) ? i : -1;
}
