/*
** EPITECH PROJECT, 2025
** int_to_str
** File description:
** Function to try and convert a given integer into a string.
*/

void int_to_str(int nbr, char *buffer)
{
    int total = 1;
    int i = 0;

    while (total * 10 <= nbr)
        total *= 10;
    for (i = 0; total; i++) {
        buffer[i] = (nbr / total) + '0';
        nbr -= (nbr / total) * total;
        total /= 10;
    }
    buffer[i] = 0;
}
