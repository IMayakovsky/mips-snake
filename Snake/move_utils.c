//
// Created by th on 06.06.20.
//
#include "snake.h"
#include "move_utils.h"


int parse_move(int knob_input) {
    if ((224 <= knob_input && knob_input <= 255) || (0 <= knob_input && knob_input < 32)) {
        return DIRECTION_DOWN;
    }
    else if (32 <= knob_input && knob_input < 96) {
        return DIRECTION_LEFT;
    } else if (96 <= knob_input && knob_input < 160) {
        return DIRECTION_UP;
    } else if (160 <= knob_input && knob_input < 224) {
        return DIRECTION_RIGHT;
    }
    return -1;
}


Point get_move(int move_type) {
    Point UP_MOVE = {.x = 0, .y = -1};
    Point RIGHT_MOVE = {.x = 1, .y = 0};
    Point DOWN_MOVE = {.x = 0, .y = 1};
    Point LEFT_MOVE = {.x = -1, .y = 0};
    switch (move_type) {
        case DIRECTION_DOWN:
            return DOWN_MOVE;
        case DIRECTION_UP:
            return UP_MOVE;
        case DIRECTION_RIGHT:
            return RIGHT_MOVE;
        case DIRECTION_LEFT:
            return LEFT_MOVE;
        default:
            return snake.head_move;
    }
}


Point generate_new_move(int move_type) {
    Point UP_MOVE = {.x = 0, .y = -1};
    Point RIGHT_MOVE = {.x = 1, .y = 0};
    Point DOWN_MOVE = {.x = 0, .y = 1};
    Point LEFT_MOVE = {.x = -1, .y = 0};
    switch (move_type) {
        case DIRECTION_DOWN:
            if (!snake.head_move.x) {
                return snake.head_move;
            } else {
                return DOWN_MOVE;
            }
        case DIRECTION_UP:
            if (!snake.head_move.x) {
                return snake.head_move;
            } else {
                return UP_MOVE;
            }
        case DIRECTION_RIGHT:
            if (!snake.head_move.y) {
                return snake.head_move;
            } else {
                return RIGHT_MOVE;
            }
        case DIRECTION_LEFT:
            if (!snake.head_move.y) {
                return snake.head_move;
            } else {
                return LEFT_MOVE;
            }
        default:
            return snake.head_move;
    }
}