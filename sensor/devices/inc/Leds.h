#ifndef LEDS_H
#define LEDS_H

typedef enum {
    LED_GREEN = 0,
    LED_YELLOW,
    LED_RED
} Led_t;

void Leds_Init(void);
void Leds_TurnOn(Led_t led);
void Leds_TurnOff(Led_t led);
void Leds_ClearAll(void);

#endif /* LEDS_H */
