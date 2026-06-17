#include "Procesamiento.h"

// Dispositivos
#include "UART.h"
#include "SensorSharp.h"
#include "SensorHCSR04.h"

// Servicios
#include "ConversionToCm_HCSR04.h"
#include "ConversionToCm_Sharp.h"
#include "ComunicacionUART.h"
#include "TimeService.h"

void Procesamiento_Init(void) {
    // Inicializar toda la arquitectura de Dispositivos (Pines, ADC, DMA, Timer)
    //a) Dispositivos:
	UART3_Init();
	SensorSharp_Init();
    SensorHCSR04_Init();

    //b) Servicios:
    TimeService_Init();

    return;
}

void Procesamiento_Update(void) {
	// Cada 500 ms de forma NO bloqueante
	if (TimeService_CheckAndClearTimeout(500)) {
		// 1. Recolectamos telemetria procesada de ambos servicios
	    uint8_t distancia_sharp = ConversionToCm_Sharp_GetDistancia();
	    uint16_t distancia_hcsr04 = ConversionToCm_HCSR04_GetDistancia();


	    // 2. Transmitimos por UART
	    ComunicacionUART_EnviarDistancias(distancia_sharp, distancia_hcsr04);
	}

	// OPCIONAL: Lógica de toma de decisiones
	/*
	if (d_sharp <= 10 || d_ultra <= 15) {
		// Frenar robot / Prender Alarma
	}
	*/

    return;
}
