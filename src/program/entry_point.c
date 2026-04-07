/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** Entry point of the program.
*/

#include "./../../include/my_radar.h"

double f_abs(double __x)
{
    return (__x < 0) ? __x * (double)-1 : __x;
}

float calculate_rotation(plane_array_t *plane)
{
    int total_x = (int)plane->end.x - (int)plane->begin.x;
    int total_y = (int)plane->end.y - (int)plane->begin.y;
    int total = abs(total_x) + abs(total_y);
    float rota = (total == 0) ? 0 : acosf((float)total_x / (float)total);

    return (total_y >= 0) ? 57.3 * rota : -57.3 * rota;
}

vector2f_t calculate_movement_vector(vector2_t *begin,
    vector2_t *end, double speed)
{
    vector2f_t movement_v = {0, 0};
    double mov_x = end->x - begin->x;
    double mov_y = end->y - begin->y;
    double total = f_abs(mov_x) + f_abs(mov_y);

    movement_v.x = speed * (mov_x / total);
    movement_v.y = speed * (mov_y / total);
    return movement_v;
}

static void tower_list_to_array(main_t *main)
{
    tower_t *t_node = main->lists.tower_head;
    tower_array_t *t_cell = &main->lists.tower_array[0];

    for (unsigned int i = 0; i < main->ids.tower_id; i++) {
        t_cell = &main->lists.tower_array[i];
        t_cell->pos.x = t_node->pos.x;
        t_cell->pos.y = t_node->pos.y;
        t_cell->radius = t_node->radius;
        t_node = t_node->next;
    }
}

static void plane_list_to_array(main_t *main)
{
    plane_t *p_node = main->lists.plane_head;
    plane_array_t *p_cell = &main->lists.plane_array[0];

    for (int i = 0; i < (int)main->ids.plane_id; i++) {
        p_cell = &main->lists.plane_array[i];
        p_cell->id = p_node->id;
        p_cell->jump_to_next = 1;
        p_cell->speed = p_node->speed;
        p_cell->delay = p_node->delay;
        p_cell->begin.x = p_node->begin.x;
        p_cell->begin.y = p_node->begin.y;
        p_cell->end.x = p_node->end.x;
        p_cell->end.y = p_node->end.y;
        p_cell->current.x = ON_DELAY;
        p_cell->current.y = p_node->begin.y;
        p_cell->rotation = calculate_rotation(p_cell);
        p_cell->per_second = calculate_movement_vector(&p_cell->begin,
            &p_cell->end, (double)p_cell->speed);
        p_node = p_node->next;
    }
}

static int prepare_arrays(main_t *main)
{
    main->lists.plane_array = c_alloc(main->ids.plane_id + 1,
        sizeof(plane_array_t));
    if (!main->lists.plane_array)
        return EXIT_FAIL;
    main->lists.plane_array[main->ids.plane_id].speed = (char)0;
    main->lists.tower_array = c_alloc(main->ids.tower_id + 1,
        sizeof(tower_array_t));
    if (!main->lists.tower_array)
        return EXIT_FAIL;
    main->lists.tower_array[main->ids.tower_id].radius = (char)0;
    tower_list_to_array(main);
    plane_list_to_array(main);
    free_linked_lists(main);
    return EXIT_SUCC;
}

static int create_shapes(main_t *main)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    sfCircleShape *circle = sfCircleShape_create();
    sfColor f1 = (sfColor){0, 0, 0, 0};
    sfColor o1 = (sfColor){0, 255, 0, 255};
    sfColor f2 = (sfColor){150, 150, 255, 255};

    if (!rect || !circle) {
        clear_program(main);
        return EXIT_FAIL;
    }
    sfRectangleShape_setFillColor(rect, f1);
    sfRectangleShape_setOutlineColor(rect, o1);
    sfRectangleShape_setOutlineThickness(rect, (float)1);
    sfCircleShape_setFillColor(circle, f2);
    sfCircleShape_setOutlineColor(circle, f1);
    sfCircleShape_setOutlineThickness(circle, (float)1);
    sfRectangleShape_setSize(rect, (sfVector2f){(float)20, (float)20});
    main->game.plane_hitbox = rect;
    main->game.tower_radius = circle;
    return EXIT_SUCC;
}

static int program_setup(main_t *main)
{
    sfRenderWindow *window = sfRenderWindow_create(
        (sfVideoMode){1920, 1080, 32}, "My radar", sfClose, NULL);
    sfTexture *plane_texture = sfTexture_createFromFile(PLANE_TEXTURE, NULL);
    sfTexture *tower_texture = sfTexture_createFromFile(TOWER_TEXTURE, NULL);
    sfSprite *plane_sprite = sfSprite_create();
    sfSprite *tower_sprite = sfSprite_create();
    sfClock *clock = sfClock_create();

    if (!(window && plane_texture && tower_texture
            && plane_sprite && tower_sprite && clock)) {
        clear_program(main);
        return EXIT_FAIL;
    }
    main->game.window = window;
    main->game.plane_texture = plane_texture;
    main->game.tower_texture = tower_texture;
    main->game.plane_sprite = plane_sprite;
    main->game.tower_sprite = tower_sprite;
    main->game.clock = clock;
    return EXIT_SUCC;
}

int program_entry_point(main_t *main)
{
    if (program_setup(main) == EXIT_FAIL)
        return EXIT_FAIL;
    if (create_text(main) == EXIT_FAIL) {
        clear_program(main);
        return EXIT_FAIL;
    }
    sfRenderWindow_setFramerateLimit(main->game.window, (unsigned int)60);
    sfSprite_setTexture(main->game.plane_sprite,
        main->game.plane_texture, sfFalse);
    sfSprite_setTexture(main->game.tower_sprite,
        main->game.tower_texture, sfFalse);
    sfSprite_setOrigin(main->game.plane_sprite, (sfVector2f){10, 10});
    if (create_shapes(main) == EXIT_FAIL)
        return EXIT_FAIL;
    sfRectangleShape_setOrigin(main->game.plane_hitbox, (sfVector2f){10, 10});
    if (prepare_arrays(main) == EXIT_FAIL) {
        clear_program(main);
        return EXIT_FAIL;
    }
    return main_loop(main);
}
