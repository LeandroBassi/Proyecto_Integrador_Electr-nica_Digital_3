#include "TimeService.h"
#include "LPC17xx.h"

// Variable estática privada para llevar la cuenta global
static volatile uint32_t tick_ms = 0;
static uint32_t last_check_time = 0;

void TimeService_Init(void) {
    // SysTick a 1ms
    SysTick_Config(SystemCoreClock / 1000);
}

void SysTick_Handler(void) {
    tick_ms++;
}

bool TimeService_CheckAndClearTimeout(uint32_t ms_interval) {
    // Calculamos si la diferencia entre el tiempo actual y la última vez supera el intervalo
    if ((tick_ms - last_check_time) >= ms_interval) {
        last_check_time = tick_ms; 		// Actualizamos marca de tiempo
        return true;
    }
    return false;
}

uint32_t TimeService_GetTicks(void) {
    return tick_ms;
}
