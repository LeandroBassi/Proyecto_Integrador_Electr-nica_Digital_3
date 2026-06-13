#ifndef LEDS_H
#define LEDS_H

typedef enum {
    LED_VERDE = 0,
    LED_AMARILLO,
    LED_ROJO
} Led_t;

void Leds_Init(void);
void Leds_Prender(Led_t led);
void Leds_Apagar(Led_t led);
void Leds_ClearAll(void);

#endif /* LEDS_H */
