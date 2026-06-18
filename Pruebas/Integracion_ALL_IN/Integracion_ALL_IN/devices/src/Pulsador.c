#include "Pulsador.h"
#include "Alarma.h"
#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_exti.h"
#include "TimeService.h"

// ---------------------------------------------------------
// DEFINICION DE MACROS
// ---------------------------------------------------------
#define DEBOUNCE_MS 250

// ---------------------------------------------------------
// PROTOTIPOS DE FUNCIONES PRIVADAS
// ---------------------------------------------------------
static void cfgGPIO(void);
static void cfgEINT0(void);

// ---------------------------------------------------------
// FUNCIONES PUBLICAS
// ---------------------------------------------------------
void Pulsador_Init(void) {
	cfgGPIO();
	cfgEINT0();
}

void EINT0_IRQHandler(void) {
    // Antirrebote: ignoramos la interrupción si llegó
    // antes de DEBOUNCE_MS desde la última vez
	static uint32_t ultimo_disparo = 0;
	uint32_t tiempo_actual = TimeService_GetTicks();

	if ((tiempo_actual - ultimo_disparo) > DEBOUNCE_MS) {
		ultimo_disparo = tiempo_actual;
	    Alarma_ToggleMute();
	}

    //EXTI_ClearEXTIFlag(EXTI_EINT0);
    LPC_SC->EXTINT = (1 << 0);
}

// ---------------------------------------------------------
// DEFINICION DE FUNCIONES PRIVADAS
// ---------------------------------------------------------
void cfgGPIO(void) {
	//-- 1)Estructura de configuracion --
	//a) Configuracion P2.10 EINT0
    PINSEL_CFG_Type cfgEINT0;

    cfgEINT0.Portnum = PINSEL_PORT_2;
    cfgEINT0.Pinnum = PINSEL_PIN_10;
    cfgEINT0.Funcnum = PINSEL_FUNC_1;
    cfgEINT0.Pinmode = PINSEL_PINMODE_TRISTATE;
    cfgEINT0.OpenDrain = PINSEL_PINMODE_NORMAL;

    PINSEL_ConfigPin(&cfgEINT0);

    return;
}

void cfgEINT0(void) {
	/*
    EXTI_InitTypeDef cfgEINT0;

    cfgEINT0.EXTI_Line = EXTI_EINT0;
    cfgEINT0.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
    cfgEINT0.EXTI_polarity = EXTI_POLARITY_HIGH_ACTIVE_OR_RISING_EDGE;

    EXTI_Config(&cfgEINT0);

    EXTI_ClearEXTIFlag(EXTI_EINT0);
    */

	// 1. Configura EINT0 sensible a FLANCO (Edge)
	LPC_SC->EXTMODE |= (1 << 0);

	// 2. Configura EINT0 sensible a flanco de SUBIDA (Rising Edge)
	LPC_SC->EXTPOLAR |= (1 << 0);

	// 3. Limpiamos  flag
	LPC_SC->EXTINT = (1 << 0);

    NVIC_EnableIRQ(EINT0_IRQn);

    return;
}
