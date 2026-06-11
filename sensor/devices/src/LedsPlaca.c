#include "LedsPlaca.h"

// Verde P0.22, Amarillo P0.21, Rojo P0.20
void LedsPlaca_Init(void) {
    LPC_GPIO0->FIODIR |= (1 << 22) | (1 << 21) | (1 << 20);
    LPC_GPIO0->FIOCLR = (1 << 22) | (1 << 21) | (1 << 20);
}

void LedsPlaca_SetState(uint8_t green, uint8_t yellow, uint8_t red) {
    LPC_GPIO0->FIOCLR = (1 << 22) | (1 << 21) | (1 << 20);
    if (green)  LPC_GPIO0->FIOSET = (1 << 22);
    if (yellow) LPC_GPIO0->FIOSET = (1 << 21);
    if (red)    LPC_GPIO0->FIOSET = (1 << 20);
}
