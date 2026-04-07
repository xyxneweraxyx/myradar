/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** Draw part of the program.
*/

#include "./../../include/my_radar.h"

int clamp(int x, int min, int max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

static void draw_towers(main_t *main)
{
    tower_array_t cell = main->lists.tower_array[0];
    sfVector2f pos;

    for (int i = 0; (int)main->lists.tower_array[i].radius != 0; i++) {
        cell = main->lists.tower_array[i];
        pos = (sfVector2f){(float)cell.pos.x - 32, (float)cell.pos.y - 32};
        sfSprite_setPosition(main->game.tower_sprite, pos);
        sfRenderWindow_drawSprite(main->game.window,
            main->game.tower_sprite, NULL);
    }
}

static void draw_planes_normal(main_t *main)
{
    plane_array_t cell = main->lists.plane_array[0];
    sfVector2f pos;

    for (int i = (int)main->lists.p_array_start;
        (int)main->lists.plane_array[i].speed != 0;
        i += main->lists.plane_array[i].jump_to_next) {
        cell = main->lists.plane_array[i];
        if (cell.current.x == NO_DRAW || cell.current.x == ON_DELAY)
            continue;
        pos = (sfVector2f){(float)cell.current.x, (float)cell.current.y};
        sfSprite_setPosition(main->game.plane_sprite, pos);
        sfSprite_setRotation(main->game.plane_sprite, cell.rotation);
        sfRenderWindow_drawSprite(main->game.window,
            main->game.plane_sprite, NULL);
    }
}

bool update_ignore_cells(plane_array_t *cell, bool *ignore_cells)
{
    int x = (int)round(((double)cell->current.x) / OCCLU_FCT);
    int y = (int)round(((double)cell->current.y) / OCCLU_FCT);

    if (ignore_cells[(1080 / OCCLU_FCT) * x + y] == true)
        return false;
    ignore_cells[(1080 / OCCLU_FCT) * x + y] = true;
    return true;
}

static void draw_planes_occlusion(main_t *main)
{
    plane_array_t cell = main->lists.plane_array[0];
    bool ignore_cells[(1920 / OCCLU_FCT) * ((1080 / OCCLU_FCT) + 1)] = {false};

    for (int i = (int)main->lists.p_array_start;
        (int)main->lists.plane_array[i].speed != 0;
        i += main->lists.plane_array[i].jump_to_next) {
        cell = main->lists.plane_array[i];
        if (cell.current.x == NO_DRAW || cell.current.x == ON_DELAY)
            continue;
        if (update_ignore_cells(&cell, ignore_cells) == false)
            continue;
        sfSprite_setPosition(main->game.plane_sprite,
            (sfVector2f){(float)cell.current.x, (float)cell.current.y});
        sfSprite_setRotation(main->game.plane_sprite, cell.rotation);
        sfRenderWindow_drawSprite(main->game.window,
            main->game.plane_sprite, NULL);
    }
}

static void draw_plane_hitboxes(main_t *main)
{
    plane_array_t p_cell = main->lists.plane_array[0];
    sfVector2f pos = {0, 0};

    for (int i = (int)main->lists.p_array_start;
        (int)main->lists.plane_array[i].speed != 0;
        i += main->lists.plane_array[i].jump_to_next) {
        p_cell = main->lists.plane_array[i];
        if (p_cell.current.x == NO_DRAW || p_cell.current.x == ON_DELAY)
            continue;
        pos = (sfVector2f){(float)p_cell.current.x, (float)p_cell.current.y};
        sfRectangleShape_setPosition(main->game.plane_hitbox, pos);
        sfRectangleShape_setRotation(main->game.plane_hitbox, p_cell.rotation);
        sfRenderWindow_drawRectangleShape(main->game.window,
            main->game.plane_hitbox, NULL);
    }
}

static void draw_plane_hitboxes_occlusion(main_t *main)
{
    plane_array_t p_cell = main->lists.plane_array[0];
    bool ignore_cells[(1920 / OCCLU_FCT) * ((1080 / OCCLU_FCT) + 1)] = {false};

    for (int i = (int)main->lists.p_array_start;
        (int)main->lists.plane_array[i].speed != 0;
        i += main->lists.plane_array[i].jump_to_next) {
        p_cell = main->lists.plane_array[i];
        if (p_cell.current.x == NO_DRAW || p_cell.current.x == ON_DELAY)
            continue;
        if (update_ignore_cells(&p_cell, ignore_cells) == false)
            continue;
        sfRectangleShape_setPosition(main->game.plane_hitbox,
            (sfVector2f){(float)p_cell.current.x, (float)p_cell.current.y});
        sfRectangleShape_setRotation(main->game.plane_hitbox, p_cell.rotation);
        sfRenderWindow_drawRectangleShape(main->game.window,
            main->game.plane_hitbox, NULL);
    }
}

void draw_tower_hitboxes(main_t *main)
{
    tower_array_t t_cell = main->lists.tower_array[0];
    sfVector2f pos = {0, 0};

    for (int i = 0; (int)main->lists.tower_array[i].radius != 0; i++) {
        t_cell = main->lists.tower_array[i];
        pos = (sfVector2f){(float)t_cell.pos.x - t_cell.radius,
            (float)t_cell.pos.y - t_cell.radius};
        sfCircleShape_setRadius(main->game.tower_radius, (float)t_cell.radius);
        sfCircleShape_setPosition(main->game.tower_radius, pos);
        sfRenderWindow_drawCircleShape(main->game.window,
            main->game.tower_radius, NULL);
    }
}

void draw_hitboxes(main_t *main)
{
    if (main->runtime.hitbox_shown == true) {
        draw_tower_hitboxes(main);
        if (main->runtime.occlusion == false)
            draw_plane_hitboxes(main);
        if (main->runtime.occlusion == true &&
            main->runtime.planes_alive < 1000)
            draw_plane_hitboxes(main);
        if (main->runtime.occlusion == true &&
            main->runtime.planes_alive >= 1000)
            draw_plane_hitboxes_occlusion(main);
    }
}

int draws(main_t *main)
{
    draw_hitboxes(main);
    if (main->runtime.sprite_shown == false)
        return EXIT_SUCC;
    draw_towers(main);
    if (main->runtime.occlusion == false)
        draw_planes_normal(main);
    if (main->runtime.occlusion == true && main->runtime.planes_alive < 1000)
        draw_planes_normal(main);
    if (main->runtime.occlusion == true && main->runtime.planes_alive >= 1000)
        draw_planes_occlusion(main);
    return EXIT_SUCC;
}
