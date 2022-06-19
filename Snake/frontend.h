//
// Created by th on 07.06.20.
//
#ifndef FRONTEND_H
#define FRONTEND_H

#include <stdint.h>
#include "point.h"

#define SNAKE_COLOR 0xf600
#define FRAME_COLOR 0xf850
#define APPLE_COLOR 0xf267
#define EMPTY 0x0
#define LCD_REG_BASE 0xffe00000

#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 320

#define FRAME_WIDTH 260
#define FRAME_HEIGHT 200

void init_frontend();
int get_color(int x, int y);
void draw_initial_snake(volatile uint16_t *screen_mem_base);
void draw_move(volatile uint16_t *screen_mem_base);
void draw_apple(volatile uint16_t *screen_mem_base, int i);
void draw_apples(volatile uint16_t *screen_mem_base);
void draw_frame(volatile uint16_t *screen_mem_base);
void print_text(volatile uint16_t *screen_mem_base, char * text, Point p_start, int p_color);

Point *frame;

#endif //FRONTEND_H
