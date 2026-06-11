#ifndef LEDSPLACA_H
#define LEDSPLACA_H

#include "LPC17xx.h"

void LedsPlaca_Init(void);
void LedsPlaca_SetState(uint8_t green, uint8_t yellow, uint8_t red);

#endif /* LEDSPLACA_H */
