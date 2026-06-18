/*******************************************************************//**
* @file	    TimeService.c
* @brief 	Implementación del servicio de tiempo
* @details	Maneja el conteo de tiempo mediante el SysTick del microcontrolador.
* @note		ESW.2.1.7
**********************************************************************/

#include "TimeService.h"
#include "LPC17xx.h"

// Variable estática privada para llevar la cuenta global
static volatile uint32_t tick_ms = 0;
static uint32_t last_check_time = 0;

/*******************************************************************//**
* @brief 	Inicializa el servicio de tiempo
* @details	Configura los recursos necesarios para la gestión de tiempo (ej. SysTick).
* @note		USW.2.1.7.1
**********************************************************************/
void TimeService_Init(void) {
    // SysTick a 1ms
    SysTick_Config(SystemCoreClock / 1000);
}

/*******************************************************************//**
* @brief 	Handler de la interrupción SysTick
* @details	Incrementa el contador de milisegundos del sistema.
* @note		USW.2.1.7.4
**********************************************************************/
void SysTick_Handler(void) {
    tick_ms++;
}

/*******************************************************************//**
* @brief 	Verifica y limpia un timeout
* @details	Retorna 'true' si ha transcurrido el intervalo especificado desde la última verificación.
* @note		USW.2.1.7.2
**********************************************************************/
bool TimeService_CheckAndClearTimeout(uint32_t ms_interval) {
    // Calculamos si la diferencia entre el tiempo actual y la última vez supera el intervalo
    if ((tick_ms - last_check_time) >= ms_interval) {
        last_check_time = tick_ms; 		// Actualizamos marca de tiempo
        return true;
    }
    return false;
}

/*******************************************************************//**
* @brief 	Obtiene los ticks actuales
* @details	Retorna el contador de milisegundos transcurridos desde el inicio.
* @note		USW.2.1.7.3
**********************************************************************/
uint32_t TimeService_GetTicks(void) {
    return tick_ms;
}
