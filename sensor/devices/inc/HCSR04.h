#ifndef HCSR04_H
#define HCSR04_H

#include "LPC17xx.h"

void HCSR04_Init(void);
void HCSR04_Trigger(void);
uint32_t HCSR04_GetEchoWidth(void);

#endif /* HCSR04_H */
