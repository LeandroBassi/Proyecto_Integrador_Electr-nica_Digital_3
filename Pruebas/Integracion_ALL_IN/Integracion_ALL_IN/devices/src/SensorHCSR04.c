#include "SensorHCSR04.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_pinsel.h"

// ---------------------------------------------------------
// DEFINICION DE MACROS
// ---------------------------------------------------------
#define TRIG_PORT (uint8_t)0
#define TRIG_PIN  ((uint32_t)(1<<5))
#define ECHO_PORT (uint8_t)1
#define ECHO_PIN  ((uint32_t)(1<<26))

// ---------------------------------------------------------
// DEFINICION DE VARIABLES GLOBALES
// ---------------------------------------------------------
static volatile uint32_t t_inicio = 0;
static volatile uint32_t tiempo_vuelo_us = 0;
static volatile bool flag_dato_listo = false;

// ---------------------------------------------------------
// PROTOTIPOS DE FUNCIONES PRIVADAS
// ---------------------------------------------------------
static void cfgGPIO(void);
static void cfgTIMER0(void);

// ---------------------------------------------------------
// FUNCIONES PUBLICAS
// ---------------------------------------------------------
void SensorHCSR04_Init(void) {
    cfgGPIO();
    cfgTIMER0();
    SensorHCSR04_Trigger();
}

void SensorHCSR04_Trigger(void) {
    flag_dato_listo = false;

    // Disparamos pulso en ALTO
    GPIO_SetValue(TRIG_PORT, TRIG_PIN);

    // Pequeño retardo bloqueante de ~10us para el disparo (300)
    for(volatile int i=0; i<300; i++);

    // Bajamos el pulso
    GPIO_ClearValue(TRIG_PORT, TRIG_PIN);
}

bool SensorHCSR04_IsDataReady(void) {
    return flag_dato_listo;
}

uint32_t SensorHCSR04_GetPulseUs(void) {
    // Almacenamos el resultado capturado por la interrupción
    return tiempo_vuelo_us;
}

// ---------------------------------------------------------
// DEFINICION DE FUNCIONES PRIVADAS
// ---------------------------------------------------------
static void cfgGPIO(void) {
	//-- 1)Estructuras de Configuracion --
    //A)Configuración P1.26 CAP0.0: ECHO
    PINSEL_CFG_Type cfgECHO_CAP0_0;

    //B)Configuracion P0.5 OUTPUT: TRIGGER
    PINSEL_CFG_Type cfgTRIG;

    //-- A)cfgECHO_CAP0_0 --
    cfgECHO_CAP0_0.Portnum = PINSEL_PORT_1;
    cfgECHO_CAP0_0.Pinnum = PINSEL_PIN_26;
    cfgECHO_CAP0_0.Funcnum = PINSEL_FUNC_3;
    cfgECHO_CAP0_0.OpenDrain = PINSEL_PINMODE_NORMAL;

    //-- B)cfgTRIG --
    cfgTRIG.Portnum = PINSEL_PORT_0;
    cfgTRIG.Pinnum = PINSEL_PIN_5;
    cfgTRIG.Funcnum = PINSEL_FUNC_0;
    cfgTRIG.OpenDrain = PINSEL_PINMODE_NORMAL;

    GPIO_SetDir(TRIG_PORT, TRIG_PIN, 1);
    GPIO_ClearValue(TRIG_PORT, TRIG_PIN);

    //-- 2)Inicializacion de cada uno --
    PINSEL_ConfigPin(&cfgECHO_CAP0_0);
    PINSEL_ConfigPin(&cfgTRIG);

    return;
}

static void cfgTIMER0(void) {
	//-- 1)Estructuras de configuracion --
    //A)Configuración de Timer en Modo Temporizador
    TIM_TIMERCFG_Type cfgTimerMode;

    //B)Configuración CAPTURE
    TIM_CAPTURECFG_Type cfgCAPTURE;

    //-- A)cfgTimerMode --
    cfgTimerMode.PrescaleOption = TIM_PRESCALE_USVAL;
    cfgTimerMode.PrescaleValue = 1; 					// Ajustado a 1ms

    //-- B)cfgCAPTURE --
    cfgCAPTURE.CaptureChannel = 0;
    cfgCAPTURE.RisingEdge = ENABLE;
    cfgCAPTURE.FallingEdge = ENABLE;
    cfgCAPTURE.IntOnCaption = ENABLE;

    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &cfgTimerMode);
    TIM_ConfigCapture(LPC_TIM0, &cfgCAPTURE);
    TIM_ResetCounter(LPC_TIM0);
    TIM_Cmd(LPC_TIM0, ENABLE);

    NVIC_EnableIRQ(TIMER0_IRQn);
    NVIC_SetPriority(TIMER0_IRQn, 1); // Alta prioridad para precisión de tiempo

    return;
}

void TIMER0_IRQHandler(void) {
    // Verificamos si la interrupción fue causada por CAP0.0
    if (TIM_GetIntStatus(LPC_TIM0, 4)) {

        // Leemos el valor del contador exacto
        uint32_t capture_val = TIM_GetCaptureValue(LPC_TIM0, 0);

        static uint8_t flanco = 0;

        if (flanco == 0) {
            // Primera captura → flanco de subida
            t_inicio = capture_val;
            flanco = 1;
        } else {
            // Segunda captura → flanco de bajada
            tiempo_vuelo_us = capture_val - t_inicio;
            flag_dato_listo = true;
            flanco = 0; // Reiniciamos para la próxima medición
        }

        // Limpiamos la bandera
        //TIM_ClearIntCapturePending(LPC_TIM0, TIM_CR0_INT) (nose porque me fallaba)
        LPC_TIM0->IR = (1 << 4);
    }
}
