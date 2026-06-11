#include "Display7SegHW.h"

void Display7SegHW_Init(void) {
    LPC_GPIO2->FIODIR |= 0xFF; // P2.0-P2.7
    LPC_GPIO2->FIOCLR = 0xFF;

    LPC_GPIO0->FIODIR |= (0xF << 10); // P0.10-P0.13
    LPC_GPIO0->FIOSET = (0xF << 10); 
}

void Display7SegHW_SetSegments(uint8_t pattern) {
    LPC_GPIO2->FIOCLR = 0xFF;
    LPC_GPIO2->FIOSET = pattern;
}

void Display7SegHW_SelectDigit(uint8_t digit_idx) {
    LPC_GPIO0->FIOSET = (0xF << 10); // Apagar todos
    if (digit_idx < 4) {
        LPC_GPIO0->FIOCLR = (1 << (10 + digit_idx)); // Activar
    }
}
