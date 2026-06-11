#include "HCSR04.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_clkpwr.h"

volatile uint32_t echo_start = 0;
volatile uint32_t echo_end = 0;
volatile uint32_t echo_width = 0;
volatile uint8_t echo_ready = 0;

void HCSR04_Init(void) {
    PINSEL_CFG_Type pinCfg;
    
    // Trigger P0.4
    pinCfg.Portnum = PINSEL_PORT_0;
    pinCfg.Pinnum = PINSEL_PIN_4;
    pinCfg.Funcnum = PINSEL_FUNC_0;
    PINSEL_ConfigPin(&pinCfg);
    FIO_SetDir(0, (1 << 4), 1);
    
    // Echo P1.26 as CAP0.0
    pinCfg.Portnum = PINSEL_PORT_1;
    pinCfg.Pinnum = PINSEL_PIN_26;
    pinCfg.Funcnum = PINSEL_FUNC_3;
    PINSEL_ConfigPin(&pinCfg);

    // Encender Timer 0
    CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCTIM0, ENABLE);
    
    // Configurar Timer para microsegundos
    TIM_TIMERCFG_Type timCfg;
    timCfg.PrescaleOption = TIM_PRESCALE_USVAL;
    timCfg.PrescaleValue = 1;
    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timCfg);
    
    // Configurar captura
    TIM_CAPTURECFG_Type capCfg;
    capCfg.CaptureChannel = 0;
    capCfg.RisingEdge = ENABLE;
    capCfg.FallingEdge = ENABLE;
    capCfg.IntOnCaption = ENABLE;
    TIM_ConfigCapture(LPC_TIM0, &capCfg);
    
    TIM_Cmd(LPC_TIM0, ENABLE);
    NVIC_EnableIRQ(TIMER0_IRQn);
}

void HCSR04_Trigger(void) {
    FIO_SetValue(0, (1 << 4));
    for(volatile int i = 0; i < 300; i++); 
    FIO_ClearValue(0, (1 << 4));
    echo_ready = 0;
}

void TIMER0_IRQHandler(void) {
    if (TIM_GetIntCaptureStatus(LPC_TIM0, TIM_CR0_INT)) {
        TIM_ClearIntCapturePending(LPC_TIM0, TIM_CR0_INT);
        
        if (FIO_ReadValue(1) & (1 << 26)) {
            echo_start = TIM_GetCaptureValue(LPC_TIM0, TIM_COUNTER_INCAP0);
        } else {
            echo_end = TIM_GetCaptureValue(LPC_TIM0, TIM_COUNTER_INCAP0);
            echo_width = (echo_end >= echo_start) ? (echo_end - echo_start) : ((0xFFFFFFFF - echo_start) + echo_end + 1);
            echo_ready = 1;
        }
    }
}
