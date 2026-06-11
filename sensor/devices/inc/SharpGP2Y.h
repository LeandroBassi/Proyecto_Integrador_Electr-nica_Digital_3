#ifndef SHARPGP2Y_H
#define SHARPGP2Y_H

#include "LPC17xx.h"

#define ADC_BUFFER_SIZE 16

void SharpGP2Y_Init(uint32_t* dest_buffer);
void SharpGP2Y_StartConversion(void);

#endif /* SHARPGP2Y_H */
