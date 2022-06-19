#include "apple.h"
#include "snake.h"
#include "point.h"
#include "terminal.h"


#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 360

#define FRAME_WIDTH 260
#define FRAME_HEIGHT 200



Point generate_random_point(int seed) {
    int t_x = snake.head.x + seed * (snake.apples_eaten + 1) * seed;
    t_x *= t_x;
    int t_y = snake.tail.y + seed * (snake.apples_eaten + 1) * seed;
    t_y *= t_y;
    t_x *= 12347;
    t_y *= 1437;
    int upper_range_y = 240;
    int lower_range_y = 120;
    int upper_range_x = 360;
    int lower_range_x = 180;
    t_x %= (upper_range_x - lower_range_x) - 20;
    t_x = t_x < 0 ? -t_x : t_x;
    t_y %= (upper_range_y - lower_range_y) - 20;
    t_y = t_y < 0 ? -t_y : t_y;
    t_y += lower_range_y; // (80, 160);
    t_x += lower_range_x; // (140, 200);
    return GetPoint(t_x, t_y);
}

void init_apples() {
    for (int i = 0; i < APPLES_MAX_SIZE; i++) {

        apples[i] = generate_random_point(i + 1);
    }
}

void generate_new_apple(int i)
{
    apples[i] = generate_random_point(i + 1);
}