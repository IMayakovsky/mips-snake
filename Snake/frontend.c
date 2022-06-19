//
// Created by th on 07.06.20.
//
#include "frontend.h"
#include "snake.h"
#include "apple.h"
#include "font_rom8x16.c"

void init_frontend()
{
    frame->x = (WINDOW_WIDTH - FRAME_WIDTH) / 2;
    frame->y = (WINDOW_HEIGHT - FRAME_HEIGHT) / 2;
}

int get_color(int x, int y) {
    volatile uint16_t *screen_mem_base = (volatile uint16_t *) LCD_REG_BASE;
    int fb_index = y*WINDOW_WIDTH + x;
    return screen_mem_base[fb_index];
}

void draw_initial_snake(volatile uint16_t *screen_mem_base) {
    for (int i = 0; i < snake.size; ++i) {
        int fb_index = snake.tail.y*WINDOW_WIDTH + snake.tail.x + i;
        screen_mem_base[fb_index] = SNAKE_COLOR;
    }
}

void draw_move(volatile uint16_t *screen_mem_base) {
    int fb_tail_index = snake.tail.y*WINDOW_WIDTH + snake.tail.x;
    int fb_head_index = snake.head.y*WINDOW_WIDTH + snake.head.x;
    screen_mem_base[fb_tail_index] = EMPTY;
    if (!snake.is_dead)
        screen_mem_base[fb_head_index] = SNAKE_COLOR;
}

void draw_apple(volatile uint16_t *screen_mem_base, int i) {
    int fb_apple_index = apples[i].y * WINDOW_WIDTH + apples[i].x;
    screen_mem_base[fb_apple_index] = APPLE_COLOR;
}

void draw_apples(volatile uint16_t *screen_mem_base) {
    for (int i = 0; i < APPLES_MAX_SIZE; ++i) {
        draw_apple(screen_mem_base, i);
    }
}

void draw_frame(volatile uint16_t *screen_mem_base)
{
    int fb_index;
    for (int i = frame->x; i <= FRAME_WIDTH + frame->x; i++)
    {
        fb_index = frame->y * WINDOW_WIDTH + i;
        screen_mem_base[fb_index] = FRAME_COLOR;
    }
    for (int i = frame->y; i <= FRAME_HEIGHT + frame->y; i++)
    {
        screen_mem_base[i * WINDOW_WIDTH + frame->x] = FRAME_COLOR;
        screen_mem_base[i * WINDOW_WIDTH + frame->x + FRAME_WIDTH] = FRAME_COLOR;
    }
    for (int i = frame->x; i <= FRAME_WIDTH + frame->x; i++)
    {
        fb_index = (frame->y + FRAME_HEIGHT) * WINDOW_WIDTH + i;
        screen_mem_base[fb_index] = FRAME_COLOR;
    }
}

void print_text(volatile uint16_t *screen_mem_base, char * text, Point p_start, int p_color)
{
    uint32_t start_offset = 0;
    start_offset += p_start.y * 1 * WINDOW_WIDTH;
    start_offset += p_start.x * 1;

    for(int idx = 0; text[idx]; idx++)
    {
        int start_idx = (int)(text[idx]) * 16;
        uint32_t offset = start_offset;

        for(int i = 0; i < 16; i++)
        {
            uint16_t line_to_print = (uint16_t)rom8x16_bits[start_idx + i];

            for(int j = 8; j > 0; j--)
            {
                int sign = (int)line_to_print >> (8 + j);

                if(sign % 2 == 1)
                screen_mem_base[offset] = p_color;
                offset++;
            }

            offset += 472;
        }

        start_offset += 10;
    }
}