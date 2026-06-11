#include "LedsPlaca.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"

void LedsPlaca_Init(void) {
    PINSEL_CFG_Type pinCfg;
    pinCfg.Funcnum = PINSEL_FUNC_0;
    pinCfg.Pinmode = PINSEL_PINMODE_PULLUP;
    pinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;
    
    // Verde P0.22, Amarillo P0.21, Rojo P0.20
    uint8_t pins[] = {22, 21, 20};
    for(int i=0; i<3; i++) {
        pinCfg.Portnum = PINSEL_PORT_0;
        pinCfg.Pinnum = pins[i];
        PINSEL_ConfigPin(&pinCfg);
    }
    
    GPIO_SetDir(0, (1 << 22) | (1 << 21) | (1 << 20), 1);
    GPIO_ClearValue(0, (1 << 22) | (1 << 21) | (1 << 20));
}

void LedsPlaca_SetState(uint8_t green, uint8_t yellow, uint8_t red) {
    GPIO_ClearValue(0, (1 << 22) | (1 << 21) | (1 << 20));
    if (green)  GPIO_SetValue(0, (1 << 22));
    if (yellow) GPIO_SetValue(0, (1 << 21));
    if (red)    GPIO_SetValue(0, (1 << 20));
}


void LedsPlaca_SetState(uint8_t green, uint8_t yellow, uint8_t red) {
    LPC_GPIO0->FIOCLR = (1 << 22) | (1 << 21) | (1 << 20);
    if (green)  LPC_GPIO0->FIOSET = (1 << 22);
    if (yellow) LPC_GPIO0->FIOSET = (1 << 21);
    if (red)    LPC_GPIO0->FIOSET = (1 << 20);
}
