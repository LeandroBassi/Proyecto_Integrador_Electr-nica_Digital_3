#ifndef LEDS_H
#define LEDS_H

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdint.h>
#include <stdbool.h>

typedef enum {
	LED_GREEN_1 = 9,
	LED_GREEN_2 = 8,
    LED_YELLOW = 7,
    LED_RED_1 = 6,
	LED_RED_2 = 0
} Led_t;

void Leds_Init(void);
void Led_TurnOn(Led_t led);
void Led_TurnOff(Led_t led);
void Leds_ClearAll(void);
void Led_Toggle(Led_t led);

#endif /* LEDS_H */
