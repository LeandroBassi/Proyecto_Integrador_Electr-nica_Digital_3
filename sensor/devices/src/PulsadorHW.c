#include "PulsadorHW.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

void PulsadorHW_Init(void) {
    PINSEL_CFG_Type pinCfg;
    pinCfg.Portnum = PINSEL_PORT_2;
    pinCfg.Pinnum = PINSEL_PIN_10;
    pinCfg.Funcnum = PINSEL_FUNC_1; // EINT0
    PINSEL_ConfigPin(&pinCfg);

    EXTI_InitTypeDef extiCfg;
    extiCfg.EXTI_Line = EXTI_EINT0;
    extiCfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
    extiCfg.EXTI_polarity = EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE;
    EXTI_Config(&extiCfg);
    
    NVIC_EnableIRQ(EINT0_IRQn);
}
