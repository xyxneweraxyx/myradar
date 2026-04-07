/*
** EPITECH PROJECT, 2025
** print_linked_lists
** File description:
** Functions to print the different arrays in the program.
*/

#include "./../../include/my_radar.h"

void print_plane_array(main_t *main)
{
    plane_array_t cell = main->lists.plane_array[0];

    my_printf("-- PLANE ARRAY DEBUG\n");
    for (int i = 0; (int)main->lists.plane_array[i].speed; i++) {
        cell = main->lists.plane_array[i];
        my_printf("--- PLANE CELL DEBUG\n");
        my_printf("ID is %d\n", (int)cell.id);
        my_printf("JUMP TO NEXT is %d\n", (int)cell.jump_to_next);
        my_printf("CURRENT POS is %d %d\n", (int)cell.current.x,
            (int)cell.current.y);
        my_printf("CURRENT SPEED IS (approximately) %d %d\n",
            (int)cell.per_second.x, (int)cell.per_second.y);
        my_printf("--- PLANE CELL END\n\n");
    }
    my_printf("-- PLANE ARRAY END\n");
}

void print_tower_array(main_t *main)
{
    tower_array_t cell = main->lists.tower_array[0];

    my_printf("-- TOWER ARRAY DEBUG\n");
    for (int i = 0; (int)main->lists.tower_array[i].radius; i++) {
        cell = main->lists.tower_array[i];
        my_printf("--- TOWER CELL DEBUG\n");
        my_printf("POS IS %d %d\n", (int)cell.pos.x, (int)cell.pos.y);
        my_printf("RADIUS IS %d\n", (int)cell.radius);
        my_printf("--- PLANE CELL END\n\n");
    }
    my_printf("-- TOWER ARRAY END\n");
}
