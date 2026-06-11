#ifndef DISPLAY7SEG_HW_H
#define DISPLAY7SEG_HW_H

#include "LPC17xx.h"

void Display7SegHW_Init(void);
void Display7SegHW_SetSegments(uint8_t pattern);
void Display7SegHW_SelectDigit(uint8_t digit_idx);

#endif /* DISPLAY7SEG_HW_H */
