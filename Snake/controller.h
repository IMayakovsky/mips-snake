//
// Created by th on 07.06.20.
//

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H
#define SPILED_REG_LED_LINE_o           0x004

/*
 * The register to control 8 bit RGB components of brightness
 * of the first RGB LED
 */
#define SPILED_REG_LED_RGB1_o           0x010

/*
 * The register to control 8 bit RGB components of brightness
 * of the second RGB LED
 */
#define SPILED_REG_LED_RGB2_o           0x014

#define SPILED_REG_KNOBS_8BIT_o         0x024

#define BLUE_KNOB 0
#define GREEN_KNOB 1
#define RED_KNOB 2

#include <stdint.h>

int is_knob_pressed(unsigned char *rgb_buttons_mem_base, int knob_type);
int read_from_knob(unsigned char *rgb_buttons_mem_base, int knob_type);

#endif //GAME_CONTROLLER_H
