#include "snake.h"
#include "move_utils.h"
#include "frontend.h"

/**
 * Sets the snake on the initial position
 * Sets initial size of the snake
 */
void init_snake()
{
    snake.breakpoint_to_execute = -1;
    snake.last_breakpoint = -1;
    snake.head = GetPoint(5 + frame->x + SNAKE_SIZE, FRAME_WIDTH / 2);
    snake.tail = GetPoint(5 + frame->x, FRAME_WIDTH / 2);
    snake.size = SNAKE_SIZE;
    snake.head_move.x = 1;
    snake.head_move.y = 0;
    snake.tail_move.x = 1;
    snake.tail_move.y = 0;
    snake.to_grow = 0;
    snake.is_dead = 0;
    snake.apples_eaten = 0;
    snake.want_to_exit = 0;
}

/**
 * Moves snake
 */
void snake_move_head() {
    snake.head.x += snake.head_move.x;
    snake.head.y += snake.head_move.y;
    snake.head.x %= (FRAME_WIDTH + frame->x);
    snake.head.y %= (FRAME_HEIGHT + frame->y);
}

void snake_move_tail() {
    if (!snake.collided_with_apple && !snake.to_grow) {
        if (snake.breakpoint_to_execute > -1 && snake.breakpoint_to_execute < BREAKPOINTS_MAX) {
            if (snake.tail.x == snake.breakpoints[snake.breakpoint_to_execute].x &&
                snake.tail.y == snake.breakpoints[snake.breakpoint_to_execute].y) {
                int move_type = snake.breakpoint_moves[snake.breakpoint_to_execute];
                if (snake.breakpoint_to_execute == snake.last_breakpoint) {
                    snake.breakpoint_to_execute = -1;
                    snake.last_breakpoint = -1;
                } else {
                    snake.breakpoint_to_execute ++;
                    snake.breakpoint_to_execute %= BREAKPOINTS_MAX;
                }
                snake.tail_move = get_move(move_type);
            }
        }

        snake.tail.x += snake.tail_move.x;
        snake.tail.y += snake.tail_move.y;
        snake.tail.x %= (FRAME_WIDTH + frame->x);
        snake.tail.y %= (FRAME_HEIGHT + frame->y);
    } else {
        snake.to_grow--;
    }
}

/**
 * Add breakpoint with move type to the array of all breakpoints, so the snake can move properly
 * @param move_type
 */
void snake_append_breakpoint(Point *move, int move_type) {
    snake.head_move.x = move->x;
    snake.head_move.y = move->y;
    if (snake.breakpoint_to_execute == -1) 
        snake.breakpoint_to_execute++;
    snake.last_breakpoint++;
    snake.last_breakpoint %= BREAKPOINTS_MAX;
    snake.breakpoints[snake.last_breakpoint] = snake.head;
    snake.breakpoint_moves[snake.last_breakpoint] = move_type;
}

