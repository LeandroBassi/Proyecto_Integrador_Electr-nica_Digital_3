#include "DistanciaCm.h"
#include "Alarma.h"
#include "Comunicacion.h"
#include "LPC17xx.h"

// Variables locales de servicios (simulando los headers inexistentes por ahora)
static uint32_t ms_ticks = 0;

// SysTick para cronometría no bloqueante
void SysTick_Handler(void) {
    ms_ticks++;
}

bool DistanciaCm_HitoTiempoAlcanzado(uint32_t *cronometro, uint32_t periodo_ms) {
    if ((ms_ticks - *cronometro) >= periodo_ms) {
        *cronometro = ms_ticks;
        return true;
    }
    return false;
}

bool Comunicacion_HitoTiempoAlcanzado(uint32_t *cronometro, uint32_t periodo_ms) {
    return DistanciaCm_HitoTiempoAlcanzado(cronometro, periodo_ms);
}
