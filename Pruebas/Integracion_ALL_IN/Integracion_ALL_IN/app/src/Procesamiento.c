#include "Procesamiento.h"

// Dispositivos
#include "UART.h"
#include "SensorSharp.h"
#include "SensorHCSR04.h"
#include "Buzzer.h"
#include "Leds.h"
#include "Pulsador.h"

// Servicios
#include "ConversionToCm_HCSR04.h"
#include "ConversionToCm_Sharp.h"
#include "ComunicacionUART.h"
#include "Alarma.h"
#include "TimeService.h"

void Procesamiento_Init(void) {
    // Inicializar toda la arquitectura de Software
    //a) Dispositivos:
	UART3_Init();
	SensorSharp_Init();
    SensorHCSR04_Init();
    Leds_Init();
    Buzzer_Init();
    Pulsador_Init();

    //b) Servicios:
    TimeService_Init();
    Alarma_Init();

    return;
}

void Procesamiento_Update(void) {
    uint8_t distancia_sharp = ConversionToCm_Sharp_GetDistancia();
    uint16_t distancia_hcsr04 = ConversionToCm_HCSR04_GetDistancia();

    Alarma_Update(distancia_sharp, distancia_hcsr04);

	// Cada 500 ms de forma NO bloqueante
	if (TimeService_CheckAndClearTimeout(500)) {
	    // 1. Transmitimos por UART
	    ComunicacionUART_EnviarDistancias(distancia_sharp, distancia_hcsr04);
	    SensorHCSR04_Trigger();
	}

    return;
}
