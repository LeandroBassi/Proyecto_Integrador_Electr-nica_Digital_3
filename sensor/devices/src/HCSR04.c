#include "HCSR04.h"

volatile uint32_t echo_start = 0;
volatile uint32_t echo_end = 0;
volatile uint32_t echo_width = 0;
volatile uint8_t echo_ready = 0;

void HCSR04_Init(void) {
    // Trigger: P0.4 como GPIO Salida
    LPC_PINCON->PINSEL0 &= ~(3 << 8);
    LPC_GPIO0->FIODIR |= (1 << 4);
    LPC_GPIO0->FIOCLR = (1 << 4);

    // Echo: P1.26 como CAP0.0 (Timer 0 Capture 0)
    LPC_PINCON->PINSEL3 &= ~(3 << 20);
    LPC_PINCON->PINSEL3 |= (3 << 20);

    // Configurar Timer 0 para tick de 1 microsegundo (pclk = 25MHz)
    LPC_SC->PCONP |= (1 << 1);
    LPC_TIM0->PR = 25 - 1;
    
    // Capturar en flancos ascendente y descendente, e interrupción en CAP0.0
    LPC_TIM0->CCR = (1 << 0) | (1 << 1) | (1 << 2);
    
    LPC_TIM0->TCR = 1; // Arrancar Timer 0
    NVIC_EnableIRQ(TIMER0_IRQn);
}

void HCSR04_Trigger(void) {
    LPC_GPIO0->FIOSET = (1 << 4);
    for(volatile int i = 0; i < 300; i++); // ~10us
    LPC_GPIO0->FIOCLR = (1 << 4);
    echo_ready = 0;
}

void TIMER0_IRQHandler(void) {
    if (LPC_TIM0->IR & (1 << 4)) {
        LPC_TIM0->IR = (1 << 4);
        
        if (LPC_GPIO1->FIOPIN & (1 << 26)) {
            echo_start = LPC_TIM0->CR0;
        } else {
            echo_end = LPC_TIM0->CR0;
            if (echo_end >= echo_start) {
                echo_width = echo_end - echo_start;
            } else {
                echo_width = (0xFFFFFFFF - echo_start) + echo_end + 1;
            }
            echo_ready = 1;
        }
    }
}

uint32_t HCSR04_GetEchoWidth(void) {
    return echo_ready ? echo_width : 0;
}
