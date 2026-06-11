#include "PulsadorHW.h"
#include "LPC17xx.h"

void PulsadorHW_Init(void) {
    // P2.10 como EINT0
    LPC_PINCON->PINSEL4 &= ~(3 << 20);
    LPC_PINCON->PINSEL4 |= (1 << 20);
    LPC_GPIO2->FIODIR &= ~(1 << 10);
    LPC_GPIOINT->IO2IntEnF |= (1 << 10);
    NVIC_EnableIRQ(GPIO_IRQn);
}
