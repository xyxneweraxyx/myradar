/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** Header file.
*/

#ifndef MY_RADAR_H
    #define MY_RADAR_H

    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <stdbool.h>
    #include <time.h>
    #include <math.h>
    #include <SFML/Graphics.h>
    #include <SFML/System/Export.h>
    #include <SFML/System/Time.h>
    #include <SFML/System/Types.h>

    // NUMBERS
    #define EXIT_SUCC 0
    #define EXIT_FAIL 84
    #define PARSER_BUFFER_SIZE 8192
    #define OCCLU_FCT 8
    #define NO_DRAW 2000
    #define ON_DELAY 2001

    // ERROR MESSAGES
    #define NO_ARGS "./my_radar: bad arguments: use -h for help\n"
    #define PARSER_FAIL "./my_radar: parser failed.\n"
    #define PROGRAM_FAIL "./my_radar: program failed.\n"

    // PATHS
    #define PLANE_TEXTURE "./assets/images/plane.png"
    #define TOWER_TEXTURE "./assets/images/tower.png"
    #define FONT "./assets/fonts/aAnotherTag.ttf"

/// TYPE DEFINITIONS

typedef struct vector2 {
    unsigned short int x;
    unsigned short int y;
} vector2_t;

typedef struct vector2_f {
    double x;
    double y;
} vector2f_t;

typedef struct plane {
    unsigned int id;

    vector2_t begin;
    vector2_t end;

    unsigned char speed;
    unsigned char delay;

    struct plane *next;
} plane_t;

typedef struct tower {
    unsigned int id;

    vector2_t pos;
    unsigned char radius;

    struct tower *next;
} tower_t;

typedef struct tower_array {
    vector2_t pos;
    unsigned char radius;
} tower_array_t;

typedef struct plane_array {
    unsigned int id;
    unsigned int jump_to_next;

    vector2_t current;
    vector2f_t per_second;
    vector2_t begin;
    vector2_t end;

    unsigned char speed;
    unsigned char delay;
    float rotation;
} plane_array_t;

typedef struct collision {
    unsigned int plane1;
    unsigned int plane2;
    double time;
} collision_t;

typedef struct ids {
    unsigned int plane_id;
    unsigned int tower_id;
} ids_t;

typedef struct lists {
    plane_t *plane_head;
    tower_t *tower_head;
    plane_array_t *plane_array;
    tower_array_t *tower_array;
    unsigned int p_array_start;
} lists_t;

typedef struct game_t {
    sfRenderWindow *window;
    sfTexture *plane_texture;
    sfTexture *tower_texture;
    sfSprite *plane_sprite;
    sfSprite *tower_sprite;
    sfRectangleShape *plane_hitbox;
    sfCircleShape *tower_radius;
    sfClock *clock;
    sfText *text;
    sfFont *font;
} game_t;

typedef struct runtime {
    bool hitbox_shown;
    bool sprite_shown;
    bool occlusion;
    int planes_alive;
} runtime_t;

typedef struct main {
    game_t game;
    ids_t ids;
    lists_t lists;
    runtime_t runtime;
} main_t;

/// MAIN FUNCTIONS

// PROGRAM
int program_entry_point(main_t *main);
int main_loop(main_t *main);
int draws(main_t *main);
int update_pos(main_t *main);
int update_collisions(main_t *main);
int create_text(main_t *main);
int update_text(main_t *main);

// CLEANUP
int free_linked_lists(main_t *main);
int clear_program(main_t *main);

// PARSING
int parser(const char *file_path, main_t *main);
int parse_single_line(const char *line, main_t *main);

// DEBUG
void print_plane_list(main_t *main);
void print_tower_list(main_t *main);
void print_plane_array(main_t *main);
void print_tower_array(main_t *main);
int my_printf(const char *format, ...);

/// LIB FUNCTIONS

// ALLOC
void *c_alloc(const size_t element_count, const size_t element_size);
int safe_free(int n, ...);

// STR
int str_len(const char *str);
int str_cmp(const char *str1, const char *str2);
int str_to_int(const char *str);
void int_to_str(const int nbr, char *buffer);

#endif
