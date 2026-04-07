/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** File to clear the program.
*/

#include "./../../include/my_radar.h"

static void clear_program_bis(main_t *main)
{
    if (main->game.plane_sprite)
        sfSprite_destroy(main->game.plane_sprite);
    if (main->game.tower_sprite)
        sfSprite_destroy(main->game.tower_sprite);
    if (main->game.plane_hitbox)
        sfRectangleShape_destroy(main->game.plane_hitbox);
    if (main->game.tower_radius)
        sfCircleShape_destroy(main->game.tower_radius);
    if (main->game.clock)
        sfClock_destroy(main->game.clock);
    if (main->game.text)
        sfText_destroy(main->game.text);
    if (main->game.font)
        sfFont_destroy(main->game.font);
}

int clear_program(main_t *main)
{
    if (main->game.window) {
        if (sfRenderWindow_isOpen(main->game.window))
            sfRenderWindow_close(main->game.window);
        sfRenderWindow_destroy(main->game.window);
    }
    if (main->game.plane_texture)
        sfTexture_destroy(main->game.plane_texture);
    if (main->game.tower_texture)
        sfTexture_destroy(main->game.tower_texture);
    clear_program_bis(main);
    safe_free(2, &main->lists.plane_array, &main->lists.tower_array);
    return EXIT_SUCC;
}
