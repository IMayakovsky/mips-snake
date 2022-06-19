//
// Created by th on 08.06.20.
//

#include "terminal.h"
#include <stdint.h>

void hw_terminal_print(const char* text)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        //wait until serial port is ready
        while(!(*(volatile uint32_t *)((unsigned char *)SERIAL_PORT_BASE) + SERP_TX_ST_REG_READY_m));

        *(volatile uint32_t *)((unsigned char *)SERIAL_PORT_BASE + SERP_TX_DATA_REG_o) = text[i];
    }
}