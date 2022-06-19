//
// Created by th on 07.06.20.
//

#include "controller.h"

int read_from_knob(unsigned char *rgb_buttons_mem_base, int knob_type) {
    int base = 1;
    for (int i = 0; i < knob_type; ++i) base *= 0x100;
    int knob_content = *(volatile uint32_t *) (rgb_buttons_mem_base + SPILED_REG_KNOBS_8BIT_o);
    return (knob_content / base) % 0x100;
}


int is_knob_pressed(unsigned char *rgb_buttons_mem_base, int knob_type) {
    int base = 1;
    for (int i = 0; i < knob_type; ++i) base *= 0x02;
    int knob_content = *(volatile uint32_t *) (rgb_buttons_mem_base + SPILED_REG_KNOBS_8BIT_o);
    knob_content /= 0x1000000;
    return (knob_content / base) % 2;
}