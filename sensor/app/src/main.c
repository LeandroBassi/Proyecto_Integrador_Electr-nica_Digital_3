#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include "Procesamiento.h"
#include "DistanciaCm.h"
#include "Alarma.h"
#include "Comunicacion.h"
#include "Leds.h"
#include "Buzzer.h"
#include "Pulsador.h"
#include "SensorSharp.h"
#include "SensorHCSR04.h"
#include "UART.h"

int main(void) {
    Leds_Init();
    Buzzer_Init();
    Pulsador_Init();
    SensorSharp_Init();
    SensorHCSR04_Init();
    UART3_Init();

    DistanciaCm_Init();
    Alarma_Init();
    Comunicacion_Init();

    while(1) {
        Procesamiento_Run();
    }
    return 0;
}
