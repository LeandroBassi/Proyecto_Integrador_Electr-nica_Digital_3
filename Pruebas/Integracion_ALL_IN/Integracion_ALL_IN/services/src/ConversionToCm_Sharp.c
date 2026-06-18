#include "ConversionToCm_Sharp.h"
#include "SensorSharp.h"

// Límites físicos (según DATA SHEET)
#define SHARP_DISTANCIA_MIN     10	// cm (Límite físico inferior)
#define SHARP_DISTANCIA_MAX     80	// cm (Límite físico superior)

#define CANTIDAD_PUNTOS (sizeof(tabla_sharp) / sizeof(tabla_sharp[0]))

// Estructura para tabla de calibración
typedef struct {
    uint16_t adc_val;
    uint8_t  dist_cm;
} PuntoCalibracion;

// TABLA DE CALIBRACIÓN EMPÍRICA
static const PuntoCalibracion tabla_sharp[] = {
    {2850, 10},
    {1600, 20},
    {1100, 30},
    {900,  40},
    {750,  50},
    {620,  60},
    {550,  70},
    {500,  80}
};

uint8_t ConversionToCm_Sharp_GetDistancia(void) {
    uint16_t valorCrudo = SensorSharp_GetPromedioCrudo();

    // 1. Si se detectó inestabilidad (0) o el valor es muy bajo
    if (valorCrudo == 0 || valorCrudo < tabla_sharp[CANTIDAD_PUNTOS - 1].adc_val) {
        return SHARP_DISTANCIA_MAX; // Asumimos 80 cm
    }

    // 2. Saturación inferior (Si el objeto está en el punto ciego < 10cm)
    if (valorCrudo >= tabla_sharp[0].adc_val) {
        return SHARP_DISTANCIA_MIN;
    }

    // 3. Búsqueda en la tabla e Interpolación Lineal
    for (uint8_t i = 0; i < CANTIDAD_PUNTOS - 1; i++) {
        if (valorCrudo <= tabla_sharp[i].adc_val && valorCrudo > tabla_sharp[i+1].adc_val) {
            int32_t x1 = tabla_sharp[i].adc_val;
            int32_t y1 = tabla_sharp[i].dist_cm;
            int32_t x2 = tabla_sharp[i+1].adc_val;
            int32_t y2 = tabla_sharp[i+1].dist_cm;

            int32_t dist_calculada = y1 + ((int32_t)(valorCrudo - x1) * (y2 - y1)) / (x2 - x1);
            return (uint8_t)dist_calculada;
        }
    }

    return SHARP_DISTANCIA_MAX;
}
