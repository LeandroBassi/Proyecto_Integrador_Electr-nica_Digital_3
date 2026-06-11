#include "Display7SegHW.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"

void Display7SegHW_Init(void) {
    PINSEL_CFG_Type pinCfg;
    pinCfg.Funcnum = PINSEL_FUNC_0;
    
    // Segmentos P2.0-P2.7
    for(int i=0; i<8; i++) {
        pinCfg.Portnum = PINSEL_PORT_2;
        pinCfg.Pinnum = i;
        PINSEL_ConfigPin(&pinCfg);
    }
    GPIO_SetDir(2, 0xFF, 1);
    GPIO_ClearValue(2, 0xFF);

    // Dígitos P0.10-P0.13
    for(int i=10; i<14; i++) {
        pinCfg.Portnum = PINSEL_PORT_0;
        pinCfg.Pinnum = i;
        PINSEL_ConfigPin(&pinCfg);
    }
    GPIO_SetDir(0, (0xF << 10), 1);
    GPIO_SetValue(0, (0xF << 10)); 
}

void Display7SegHW_SetSegments(uint8_t pattern) {
    GPIO_ClearValue(2, 0xFF);
    GPIO_SetValue(2, pattern);
}

void Display7SegHW_SelectDigit(uint8_t digit_idx) {
    GPIO_SetValue(0, (0xF << 10));
    if (digit_idx < 4) {
        GPIO_ClearValue(0, (1 << (10 + digit_idx)));
    }
}
