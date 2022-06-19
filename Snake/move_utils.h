//
// Created by th on 06.06.20.
//

#ifndef MOVE_UTILS_H
#define MOVE_UTILS_H

#define DIRECTION_UP 0
#define DIRECTION_RIGHT 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3

int parse_move(int knob_input);

Point get_move(int move_type);
Point generate_new_move(int move_type);

#endif //MOVE_UTILS_H
