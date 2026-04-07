/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** Main file.
*/

#include "./../include/my_radar.h"

static int write_wrap(const char *str)
{
    return write(1, str, str_len(str));
}

static int error_msg(const char *error)
{
    write(2, error, str_len(error));
    return EXIT_FAIL;
}

static int print_help(void)
{
    write_wrap("Air traffic simulation panel\n");
    write_wrap("USAGE\n");
    write_wrap("  ./my_radar [OPTIONS] path_to_script\n");
    write_wrap("    path_to_script    The path to the script file.\n");
    write_wrap("OPTIONS\n");
    write_wrap("  -h                print the usage and quit.\n");
    write_wrap("USER INTERACTIONS\n");
    write_wrap("  'L' key        enable/disable hitboxes and areas.\n");
    write_wrap("  'S' key        enable/disable sprites.\n");
    write_wrap("  'F' key        enable/disable culling (Default: enabled)\n");
    return EXIT_SUCC;
}

static void initialize_main(main_t *main)
{
    main->ids.tower_id = 0;
    main->lists.plane_head = NULL;
    main->lists.tower_head = NULL;
    main->lists.plane_array = NULL;
    main->lists.tower_array = NULL;
    main->lists.p_array_start = 0;
    main->runtime.hitbox_shown = true;
    main->runtime.sprite_shown = true;
    main->runtime.occlusion = true;
    main->runtime.planes_alive = 0;
    main->game.window = NULL;
    main->game.plane_texture = NULL;
    main->game.tower_texture = NULL;
    main->game.plane_sprite = NULL;
    main->game.tower_sprite = NULL;
    main->game.plane_hitbox = NULL;
    main->game.tower_radius = NULL;
    main->game.clock = NULL;
    main->game.text = NULL;
    main->game.font = NULL;
}

int free_linked_lists(main_t *main)
{
    plane_t *temp_p = NULL;
    tower_t *temp_t = NULL;

    while (main->lists.plane_head) {
        temp_p = main->lists.plane_head;
        main->lists.plane_head = temp_p->next;
        free(temp_p);
    }
    while (main->lists.tower_head) {
        temp_t = main->lists.tower_head;
        main->lists.tower_head = temp_t->next;
        free(temp_t);
    }
    main->lists.plane_head = NULL;
    main->lists.tower_head = NULL;
    return EXIT_SUCC;
}

static int stop_program(main_t *main)
{
    if (free_linked_lists(main) == EXIT_FAIL)
        return EXIT_FAIL;
    return EXIT_SUCC;
}

int main(int argc, char **argv)
{
    main_t main;

    initialize_main(&main);
    main.ids.plane_id = 0;
    if (argc != 2)
        return error_msg(NO_ARGS);
    if (str_cmp(argv[1], "-h") == 0)
        return print_help();
    if (parser(argv[1], &main) == EXIT_FAIL) {
        stop_program(&main);
        return error_msg(PARSER_FAIL);
    }
    if (program_entry_point(&main) == EXIT_FAIL) {
        stop_program(&main);
        return error_msg(PROGRAM_FAIL);
    }
    stop_program(&main);
    return EXIT_SUCC;
}
