/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** Main loop of the program.
*/

#include "./../../include/my_radar.h"

static int events(main_t *main)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(main->game.window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(main->game.window);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyL)
            main->runtime.hitbox_shown = !main->runtime.hitbox_shown;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyS)
            main->runtime.sprite_shown = !main->runtime.sprite_shown;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyF)
            main->runtime.occlusion = !main->runtime.occlusion;
    }
    return EXIT_SUCC;
}

static int reset(main_t *main)
{
    sfRenderWindow_clear(main->game.window, sfBlack);
    return EXIT_SUCC;
}

int main_loop(main_t *main)
{
    while (sfRenderWindow_isOpen(main->game.window)) {
        if (reset(main) == EXIT_FAIL)
            break;
        if (events(main) == EXIT_FAIL)
            break;
        if (update_collisions(main) == EXIT_FAIL)
            break;
        if (update_pos(main) == EXIT_FAIL)
            break;
        if (draws(main) == EXIT_FAIL)
            break;
        if (update_text(main) == EXIT_FAIL)
            break;
        sfRenderWindow_display(main->game.window);
        if (!main->runtime.planes_alive)
            break;
    }
    if (clear_program(main) == EXIT_FAIL)
        return EXIT_FAIL;
    return EXIT_SUCC;
}
