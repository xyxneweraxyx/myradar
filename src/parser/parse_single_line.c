/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** Parse a single line.
*/

#include "./../../include/my_radar.h"

static int error_msg(const char *error)
{
    write(2, error, str_len(error));
    return EXIT_FAIL;
}

// Assuming that the line is correct
static void get_num_list(const char *line, int *result)
{
    int len = str_len(line);
    int total = 0;
    int written = 0;
    int num_len = 0;
    char buff[10] = {0};

    while (total < len) {
        for (num_len = 0; line[num_len] >= '0' &&
            line[num_len] <= '9'; num_len++)
            buff[num_len] = line[num_len];
        buff[num_len] = 0;
        result[written] = str_to_int(buff);
        line += num_len + 1;
        total += num_len + 1;
        written++;
    }
}

static int parse_plane(const char *line, main_t *main)
{
    plane_t *plane = c_alloc(1, sizeof(plane_t));
    int data[6] = {0};

    if (!plane)
        return error_msg("A plane calloc failed in the parser\n");
    line += 2;
    get_num_list(line, data);
    plane->id = main->ids.plane_id;
    main->ids.plane_id++;
    plane->begin.x = (unsigned short int)data[0];
    plane->begin.y = (unsigned short int)data[1];
    plane->end.x = (unsigned short int)data[2];
    plane->end.y = (unsigned short int)data[3];
    plane->speed = (unsigned char)data[4];
    plane->delay = (unsigned char)data[5];
    plane->next = main->lists.plane_head;
    main->lists.plane_head = plane;
    main->runtime.planes_alive++;
    return EXIT_SUCC;
}

static int parse_tower(const char *line, main_t *main)
{
    tower_t *tower = c_alloc(1, sizeof(tower_t));
    int data[3] = {0};

    if (!tower)
        return error_msg("A tower calloc failed in the parser\n");
    line += 2;
    get_num_list(line, data);
    tower->id = main->ids.tower_id;
    main->ids.tower_id++;
    tower->pos.x = (unsigned short int)data[0];
    tower->pos.y = (unsigned short int)data[1];
    tower->radius = (unsigned char)data[2];
    tower->next = main->lists.tower_head;
    main->lists.tower_head = tower;
    return EXIT_SUCC;
}

static bool assert_line(const char *line)
{
    int total = 0;
    int data[6] = {0};

    if (line[0] != 'A' && line[0] != 'T')
        return false;
    for (int i = 1; line[i]; i++) {
        if (line[i] == ' ' || (line[i] >= '0' && line[i] <= '9'
                && (line[i - 1] < '0' || line[i - 1] > '9')))
            total++;
    }
    if ((line[0] == 'A' && total != 12) || (line[0] == 'T' && total != 6))
        return false;
    line += 2;
    get_num_list(line, data);
    line -= 2;
    if ((line[0] == 'A' && data[4] == 0) || (line[0] == 'T' && data[2] == 0))
        return false;
    return true;
}

int parse_single_line(const char *line, main_t *main)
{
    if (assert_line(line) == false)
        return error_msg("A line in the file is incorrect\n");
    if (line[0] == 'A')
        return parse_plane(line, main);
    if (line[0] == 'T')
        return parse_tower(line, main);
    return error_msg("Unknown exception in the parser\n");
}
