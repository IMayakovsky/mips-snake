#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <stdio.h>
#include <stdint.h>

int score;

void start(volatile uint16_t *screen_mem_base);
void controls_update(unsigned char *rgb_buttons_mem_base, volatile uint16_t *screen_mem_base);
void drawing_update(volatile uint16_t *screen_mem_base);
int user_wants_to_exit(unsigned char *rgb_buttons_mem_base);

void draw_score(volatile uint16_t *screen_mem_base);
void clear_score(volatile uint16_t *screen_mem_base);

void snake_change_direction();

void snake_check_apple_collision(volatile uint16_t *screen_mem_base);
void snake_check_snake_collision();
void snake_die();
void check_window_borders();

#endif //GAME_MANAGER_H