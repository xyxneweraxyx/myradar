/*
** EPITECH PROJECT, 2025
** print_linked_lists
** File description:
** Functions to print the different linked lists in the program.
*/

#include "./../../include/my_radar.h"

void print_plane_list(main_t *main)
{
    my_printf("-- PLANE LIST DEBUG\n");
    for (plane_t *plane = main->lists.plane_head; plane; plane = plane->next) {
        my_printf("--- PLANE DEBUG\n");
        my_printf("ID : %d\n", (int)plane->id);
        my_printf("BEGIN : %d %d\n", (int)plane->begin.x, (int)plane->begin.y);
        my_printf("END : %d %d\n", (int)plane->end.x, (int)plane->end.y);
        my_printf("SPEED : %d\n", (int)plane->speed);
        my_printf("DELAY : %d\n", (int)plane->delay);
        my_printf("--- DEBUG END\n\n");
    }
    my_printf("-- PLANE LIST END\n");
}

void print_tower_list(main_t *main)
{
    my_printf("-- TOWER LIST DEBUG\n");
    for (tower_t *tower = main->lists.tower_head; tower; tower = tower->next) {
        my_printf("--- TOWER DEBUG\n");
        my_printf("ID : %d\n", (int)tower->id);
        my_printf("POS : %d %d\n", (int)tower->pos.x, (int)tower->pos.y);
        my_printf("RADIUS : %d\n", (int)tower->radius);
        my_printf("--- DEBUG END\n\n");
    }
    my_printf("-- TOWER LIST END\n");
}
