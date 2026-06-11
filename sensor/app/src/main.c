#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "HCSR04.h"
#include "SharpGP2Y.h"
#include "DriverDisplay.h"
#include "ComunicacionUART.h"
#include "Procesamiento.h"
#include "ConversionSharp.h"
#include "ConversionHCSR04.h"

uint32_t adc_buf[16];
volatile uint32_t ms = 0;

void SysTick_Handler(void) { ms++; DriverDisplay_Refresh(); }

int main(void) {
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000);
    HCSR04_Init();
    SharpGP2Y_Init(adc_buf);
    UART_Init(9600);
    Procesamiento_Init();
    SharpGP2Y_StartConversion();
    while(1) {
        if (ms % 60 == 0) {
            HCSR04_Trigger();
            for(int i=0; i<1000; i++);
            float d_us = HCSR04_Width_to_Distance(HCSR04_GetEchoWidth());
            uint32_t sum = 0;
            for(int i=0; i<16; i++) sum += adc_buf[i];
            float d_ir = Sharp_ADC_to_Distance(sum/16);
            Procesamiento_Actualizar(d_ir, d_us);
            DriverDisplay_SetNumber((d_us < 80.0f) ? d_ir : d_us);
        }
    }
}
