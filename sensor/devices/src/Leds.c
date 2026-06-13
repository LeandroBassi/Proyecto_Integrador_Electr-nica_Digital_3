#include "Leds.h"
#include "LPC17xx.h"

void Leds_Init(void) {
    // Configurar P0.7, P0.8, P0.9 como salida (Green, Yellow, Red)
    LPC_PINCON->PINSEL0 &= ~(0x3F << 14); 
    LPC_GPIO0->FIODIR |= (1 << 7) | (1 << 8) | (1 << 9);
    Leds_ClearAll();
}

void Leds_Prender(Led_t led) {
    switch(led) {
        case LED_VERDE:    LPC_GPIO0->FIOSET = (1 << 7); break;
        case LED_AMARILLO: LPC_GPIO0->FIOSET = (1 << 8); break;
        case LED_ROJO:     LPC_GPIO0->FIOSET = (1 << 9); break;
    }
}

void Leds_Apagar(Led_t led) {
    switch(led) {
        case LED_VERDE:    LPC_GPIO0->FIOCLR = (1 << 7); break;
        case LED_AMARILLO: LPC_GPIO0->FIOCLR = (1 << 8); break;
        case LED_ROJO:     LPC_GPIO0->FIOCLR = (1 << 9); break;
    }
}

void Leds_ClearAll(void) {
    LPC_GPIO0->FIOCLR = (1 << 7) | (1 << 8) | (1 << 9);
}
