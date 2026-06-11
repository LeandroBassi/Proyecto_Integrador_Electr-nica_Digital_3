#include "Procesamiento.h"
#include "DriverLeds.h"
#include "DriverBuzzer.h"
#include "ComunicacionUART.h"
#include "PulsadorHW.h"

static float umbral = 150.0f;
static uint8_t muted = 0;

void Procesamiento_Init(void) { 
    DriverLeds_Init(); 
    DriverBuzzer_Init(); 
    PulsadorHW_Init();
}

void Procesamiento_ToggleSilenciar(void) {
    muted = !muted;
}

void Procesamiento_Actualizar(float d_ir, float d_us) {
    float f = (d_us < 80.0f) ? d_ir : d_us;
    if (f > umbral) {
        DriverLeds_SetRango(0);
        DriverBuzzer_Stop();
    } else if (f > 50.0f) {
        DriverLeds_SetRango(1);
        if(!muted) DriverBuzzer_SetFrequency(1000 + (uint32_t)((umbral - f) * 15));
        else DriverBuzzer_Stop();
    } else {
        DriverLeds_SetRango(2);
        if(!muted) DriverBuzzer_SetFrequency(3500);
        else DriverBuzzer_Stop();
    }
}

void GPIO_IRQHandler(void) {
    if (LPC_GPIOINT->IO2IntStatF & (1 << 10)) {
        LPC_GPIOINT->IO2IntClr = (1 << 10);
        Procesamiento_ToggleSilenciar();
        UART_SendString("Alarma silenciada manualmente\r\n");
    }
}
