#include "game_manager.h"

#include "frontend.h"
#include "move_utils.h"
#include "apple.h"
#include "snake.h"
#include "controller.h"
#include "terminal.h"

void draw_score(volatile uint16_t *screen_mem_base) {
    int score = snake.apples_eaten;
    char char_score[2] = {'\0', '\0'};
    int dec = 0;
    if (!score) {
        char_score[0] = '0';
        Point p = GetPoint(320, 20);
        int offset = p.y * WINDOW_WIDTH + p.x;
        // clear a letter
        for (int i = 0; i < 16; ++i) {
            for(int j = 0; j < 8; ++j) {
                screen_mem_base[offset + i*WINDOW_WIDTH + j] = EMPTY;
            }
        }
        print_text(screen_mem_base, char_score, p, APPLE_COLOR);
    } else {
        while (score != 0) {
            char_score[0] = score % 10 + '0';
            score /= 10;
            Point p = GetPoint(320 - dec * 12, 20);
            int offset = p.y * WINDOW_WIDTH + p.x;
            // clear a letter
            for (int i = 0; i < 16; ++i) {
                for(int j = 0; j < 8; ++j) {
                    screen_mem_base[offset + i*WINDOW_WIDTH + j] = EMPTY;
                }
            }
            dec++;
            print_text(screen_mem_base, char_score, p, APPLE_COLOR);
        }
    }

}


void clear_score(volatile uint16_t *screen_mem_base) {
    int score = 1000000;
    int dec = 0;
    while (score != 0) {
        score /= 10;
        Point p = GetPoint(320 - dec * 12, 20);
        int offset = p.y * WINDOW_WIDTH + p.x;
        // clear a letter
        for (int i = 0; i < 16; ++i) {
            for(int j = 0; j < 8; ++j) {
                screen_mem_base[offset + i*WINDOW_WIDTH + j] = EMPTY;
            }
        }
        dec++;
    }
}

void start(volatile uint16_t *screen_mem_base)
{
    init_frontend();
    init_snake();
    init_apples();

    draw_frame(screen_mem_base);
    draw_initial_snake(screen_mem_base);
    draw_apples(screen_mem_base);
    Point p = GetPoint(110, 20);
    print_text(screen_mem_base, "Score: ", p, APPLE_COLOR);
    draw_score(screen_mem_base);
}

void drawing_update(volatile uint16_t *screen_mem_base)
{
    snake_move_head();
    snake_check_apple_collision(screen_mem_base);
    snake_check_snake_collision();
    draw_move(screen_mem_base);
    if (snake.collided_with_apple) 
        draw_apple(screen_mem_base, snake.apple_index);
    snake_move_tail();

    if (snake.is_dead) --snake.size;
}

void controls_update(unsigned char *rgb_buttons_mem_base, volatile uint16_t *screen_mem_base)
{
    if (is_knob_pressed(rgb_buttons_mem_base, RED_KNOB)) {
            *(volatile uint32_t *) (rgb_buttons_mem_base + SPILED_REG_LED_RGB2_o) = 0x00080085; //debug info = turned on
            snake_change_direction(rgb_buttons_mem_base, RED_KNOB);
    } else {
        *(volatile uint32_t *) (rgb_buttons_mem_base + SPILED_REG_LED_RGB2_o) = 0x51337; //debug info = turned off
    }

    //debug section

    *(volatile uint32_t *) (rgb_buttons_mem_base + SPILED_REG_LED_LINE_o) = *(volatile uint32_t *) (rgb_buttons_mem_base + SPILED_REG_KNOBS_8BIT_o);
    *(volatile uint32_t *) (rgb_buttons_mem_base + SPILED_REG_LED_RGB1_o) = snake.apples_eaten; // score
    //*(volatile uint32_t *) (rgb_buttons_mem_base + SPILED_REG_LED_RGB2_o) = SPEED;

    if (snake.is_dead && snake.size < 0) {
        if (is_knob_pressed(rgb_buttons_mem_base, GREEN_KNOB)) {
            int in = read_from_knob(rgb_buttons_mem_base, GREEN_KNOB);
            if (in >= 128) {
                clear_score(screen_mem_base);
                init_snake();
                draw_score(screen_mem_base);
            }
        }
    }

    check_window_borders();
    
}

void check_window_borders()
{
    if (snake.head.x >= FRAME_WIDTH + frame->x || snake.head.x <= frame->x 
        || snake.head.y >= FRAME_HEIGHT + frame->y || snake.head.y <= frame->y) {
        snake_die();
    }
}

void snake_check_apple_collision(volatile uint16_t *screen_mem_base) {
    for (int i = 0; i < APPLES_MAX_SIZE; ++i){
        if (snake.head.x == apples[i].x && snake.head.y == apples[i].y) {
            snake.size += SNAKE_SIZE;
            snake.to_grow += SNAKE_SIZE;
            generate_new_apple(i);
            snake.apple_index = i;
            snake.collided_with_apple = 1;
            snake.apples_eaten += 6;
            draw_score(screen_mem_base);
            return;
        }
    }
    snake.collided_with_apple = 0;
}

void snake_change_direction(unsigned char* rgb_buttons_mem_base, int knob_type) {
    int turn_knob_input = read_from_knob(rgb_buttons_mem_base, knob_type);
    int move_type = parse_move(turn_knob_input);
    Point move = generate_new_move(move_type);
    if (!(snake.head_move.x == move.x && snake.head_move.y == move.y)) 
    {
        snake_append_breakpoint(&move, move_type);
    }
}

void snake_die() {
    if (!snake.is_dead)
        hw_terminal_print("Game over. Set your green button to 128-255 to restart.\n");
    snake.is_dead = 1;
    snake.head_move = GetPoint(0, 0);
}

void snake_check_snake_collision() {
    if (get_color(snake.head.x, snake.head.y) == SNAKE_COLOR) {
        snake_die();
    }
}

int user_wants_to_exit(unsigned char* rgb_buttons_mem_base) {
    if (is_knob_pressed(rgb_buttons_mem_base, BLUE_KNOB)) {
        int in = read_from_knob(rgb_buttons_mem_base, BLUE_KNOB);
        if (in >= 128)
            return 1;
    }
    return 0;
}