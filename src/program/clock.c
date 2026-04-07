/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** File to handle the clock and the planes alive.
*/

#include "./../../include/my_radar.h"

static int buffer_write(const char *msg, char *buffer, int start)
{
    int i = 0;

    for (i = 0; msg[i]; i++)
        buffer[start + i] = msg[i];
    return i;
}

static void create_buffer(int seconds, int planes_alive, char *buffer)
{
    int current = 0;
    char time_buffer[10] = {0};
    char plane_buffer[10] = {0};

    int_to_str(seconds, time_buffer);
    int_to_str(planes_alive, plane_buffer);
    current += buffer_write("TIME : ", buffer, current);
    current += buffer_write(time_buffer, buffer, current);
    current += buffer_write("s | PLANES LEFT : ", buffer, current);
    current += buffer_write(plane_buffer, buffer, current);
    buffer[current] = '\n';
}

int create_text(main_t *main)
{
    sfText *text = sfText_create();
    sfFont *font = sfFont_createFromFile(FONT);

    if (!text || !font)
        return EXIT_FAIL;
    sfText_setFillColor(text, (sfColor){0, 0, 0, 255});
    sfText_setOutlineColor(text, (sfColor){255, 255, 255, 255});
    sfText_setOutlineThickness(text, 3);
    sfText_setCharacterSize(text, (unsigned int)70);
    sfText_setPosition(text, (sfVector2f){1350, 0});
    sfText_setFont(text, font);
    main->game.text = text;
    main->game.font = font;
    return EXIT_SUCC;
}

int update_text(main_t *main)
{
    int seconds = (int)(sfClock_getElapsedTime(main->game.clock).microseconds);
    int planes_alive = main->runtime.planes_alive;
    sfText *text = main->game.text;
    char buffer[64] = {0};

    if (!text)
        return EXIT_FAIL;
    seconds /= 1000000;
    create_buffer(seconds, planes_alive, buffer);
    sfText_setString(text, buffer);
    sfRenderWindow_drawText(main->game.window, text, NULL);
    return EXIT_SUCC;
}
