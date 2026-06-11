#ifndef BUZZERPOWER_H
#define BUZZERPOWER_H

#include "LPC17xx.h"

void BuzzerPower_Init(void);
void BuzzerPower_SetFrequency(uint32_t freq_hz);
void BuzzerPower_Stop(void);

#endif /* BUZZERPOWER_H */
