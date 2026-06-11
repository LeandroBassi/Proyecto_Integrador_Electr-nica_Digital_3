#include "BuzzerPower.h"

void BuzzerPower_Init(void) {
    // P1.18 como PWM1.1
    LPC_PINCON->PINSEL3 &= ~(3 << 4);
    LPC_PINCON->PINSEL3 |= (2 << 4);

    LPC_SC->PCONP |= (1 << 6);  // Encender PWM1
    LPC_PWM1->PR = 25 - 1;      // Timer de 1us (asumiendo pclk = 25MHz)
    LPC_PWM1->PCR = (1 << 9);   // Habilitar salida de PWM1.1
    LPC_PWM1->MCR = (1 << 1);   // Reset del timer al coincidir con MR0
    
    LPC_PWM1->MR0 = 1000;       // 1kHz
    LPC_PWM1->MR1 = 0;          // Apagado
    LPC_PWM1->LER = (1 << 0) | (1 << 1);
    LPC_PWM1->TCR = (1 << 0) | (1 << 3);
}

void BuzzerPower_SetFrequency(uint32_t freq_hz) {
    if (freq_hz == 0) {
        BuzzerPower_Stop();
        return;
    }
    uint32_t period_us = 1000000 / freq_hz;
    LPC_PWM1->MR0 = period_us;
    LPC_PWM1->MR1 = period_us / 2; // 50% duty cycle
    LPC_PWM1->LER |= (1 << 0) | (1 << 1);
}

void BuzzerPower_Stop(void) {
    LPC_PWM1->MR1 = 0;
    LPC_PWM1->LER |= (1 << 1);
}
