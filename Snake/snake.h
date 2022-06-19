#ifndef SNAKE_H
#define SNAKE_H

#include "point.h"

#define APPLES_MAX_SIZE 4
#define SPEED 1
#define BREAKPOINTS_MAX 1000

#define SNAKE_SIZE 30

typedef struct Snake
{
    int last_breakpoint;
    int breakpoint_to_execute;
    int size;
    int capacity;
    Point tail_move;
    Point head_move;
    Point head;
    Point tail;
    int breakpoint_moves[BREAKPOINTS_MAX];
    Point breakpoints[BREAKPOINTS_MAX];
    int to_grow;
    int collided_with_apple;
    int apple_index;
    int is_dead;
    int apples_eaten;
    int want_to_exit;

} Snake;

    void init_snake();
    void check_window_borders();
    void snake_move_tail();
    void snake_move_head();
    
    void snake_append_breakpoint(Point *move, int move_type);
    Snake snake;

#endif //SNAKE_H