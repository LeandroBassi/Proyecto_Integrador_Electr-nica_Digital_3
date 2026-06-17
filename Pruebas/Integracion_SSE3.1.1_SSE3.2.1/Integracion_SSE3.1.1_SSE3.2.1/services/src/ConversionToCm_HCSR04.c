#include "ConversionToCm_HCSR04.h"
#include "SensorHCSR04.h"

// Límites físicos (según DATA SHEET)
#define HCSR04_DISTANCIA_MIN    2    // cm (Límite físico inferior)
#define HCSR04_DISTANCIA_MAX    400  // cm (Límite físico superior)

// Variable estática interna para última medición válida
static uint16_t ultima_distancia_cm = HCSR04_DISTANCIA_MAX;

uint16_t ConversionToCm_HCSR04_GetDistancia(void) {
    // 1) Verificamos si el hardware ya completó la medición del pulso Echo
    if (SensorHCSR04_IsDataReady()) {

        // 2) Extraemos el tiempo de vuelo en us
        uint32_t tiempo_us = SensorHCSR04_GetPulseUs();

        // 3) Cálculo físico: Distancia = Tiempo / 58
        uint32_t dist_calculada = tiempo_us / 58;

        // 4) Saturación a los límites reales del sensor
        if (dist_calculada > HCSR04_DISTANCIA_MAX) {
            dist_calculada = HCSR04_DISTANCIA_MAX;
        }
        else if (dist_calculada < HCSR04_DISTANCIA_MIN) {
            dist_calculada = HCSR04_DISTANCIA_MIN;
        }

        // 5) Guardamos el resultado en la variable
        ultima_distancia_cm = (uint16_t)dist_calculada;

        // 6) Trigger para siguientes mediciones
        SensorHCSR04_Trigger();
    }

    return ultima_distancia_cm;
}
