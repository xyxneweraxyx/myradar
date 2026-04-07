/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** File to update the positions of the planes before drawing.
*/

#include "./../../include/my_radar.h"

static bool is_plane_finished(plane_array_t *cell)
{
    if ((abs((int)cell->current.x - (int)cell->begin.x) >
            abs((int)cell->end.x - (int)cell->begin.x)) ||
        (abs((int)cell->current.y - (int)cell->begin.y) >
            abs((int)cell->end.y - (int)cell->begin.y)))
        return true;
    return false;
}

static bool plane_in_tower_radius(main_t *main, plane_array_t *p)
{
    tower_array_t *t = &main->lists.tower_array[0];
    double center_x;
    double center_y;
    double dx;
    double dy;
    double dist;
    double r;

    for (int k = 0; (int)t[k].radius != 0; k++) {
        center_x = (double)t[k].pos.x;
        center_y = (double)t[k].pos.y;
        dx = (double)p->current.x - center_x;
        dy = (double)p->current.y - center_y;
        dist = dx * dx + dy * dy;
        r = (double)t[k].radius;
        if (dist <= r * r + 10)
            return true;
    }
    return false;
}

static bool check_and_handle_collision(main_t *main, plane_array_t *p1,
    plane_array_t *p2)
{
    int dx = abs((int)p1->current.x - (int)p2->current.x);
    int dy = abs((int)p1->current.y - (int)p2->current.y);

    if (dx >= 20 || dy >= 20)
        return false;
    if (plane_in_tower_radius(main, p1) || plane_in_tower_radius(main, p2))
        return false;
    if (p1->current.x != NO_DRAW) {
        p1->current.x = NO_DRAW;
        main->runtime.planes_alive--;
    }
    if (p2->current.x != NO_DRAW) {
        p2->current.x = NO_DRAW;
        main->runtime.planes_alive--;
    }
    return true;
}

static void check_plane_collisions(main_t *main, int i)
{
    plane_array_t *arr = &main->lists.plane_array[0];

    for (int j = i + arr[i].jump_to_next; (int)arr[j].speed != 0;
        j += arr[j].jump_to_next) {
        if (arr[j].current.x == NO_DRAW || arr[j].current.x == ON_DELAY)
            continue;
        if (check_and_handle_collision(main, &arr[i], &arr[j]))
            break;
    }
}

int update_collisions(main_t *main)
{
    plane_array_t *arr = &main->lists.plane_array[0];
    int start = (int)main->lists.p_array_start;

    for (int i = start; (int)arr[i].speed != 0; i += arr[i].jump_to_next) {
        if (arr[i].current.x == NO_DRAW || arr[i].current.x == ON_DELAY)
            continue;
        check_plane_collisions(main, i);
    }
    return EXIT_SUCC;
}

static void new_positions(plane_array_t *cell, float time)
{
    cell->current.x = (int)(cell->begin.x +
        (time - (float)cell->delay) * cell->per_second.x);
    cell->current.y = (int)(cell->begin.y +
        (time - (float)cell->delay) * cell->per_second.y);
}

int update_pos(main_t *main)
{
    plane_array_t *cell = &main->lists.plane_array[0];
    float time = (float)sfClock_getElapsedTime(main->game.clock).microseconds;

    time /= 1000000;
    for (int i = (int)main->lists.p_array_start;
        (int)main->lists.plane_array[i].speed != 0; i++) {
        cell = &main->lists.plane_array[i];
        if (cell->current.x == ON_DELAY && time >= (float)cell->delay)
            cell->current.x = cell->begin.x;
        if (cell->current.x == NO_DRAW || cell->current.x == ON_DELAY)
            continue;
        new_positions(cell, time);
        if (is_plane_finished(cell) == true) {
            main->runtime.planes_alive--;
            cell->current.x = NO_DRAW;
        }
    }
    return EXIT_SUCC;
}
