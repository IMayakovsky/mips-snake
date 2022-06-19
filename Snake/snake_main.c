#include <stdio.h>
#include <stdint.h>

#include "snake.h"
#include "game_manager.h"

#define LCD_REG_BASE 0xffe00000
#define SPILED_REG_BASE      0xffffc100

int main(void) {
    
    volatile uint16_t *screen_mem_base = (volatile uint16_t *) LCD_REG_BASE;
    unsigned char *rgb_buttons_mem_base = (unsigned char *) SPILED_REG_BASE;

    start(screen_mem_base);

    while (1) 
    {
        drawing_update(screen_mem_base);
        controls_update(rgb_buttons_mem_base, screen_mem_base);
        if (user_wants_to_exit(rgb_buttons_mem_base)) return 0;
    }
    __asm__ __volatile__ ("break\n" : : : "memory");

    return 0;
}
