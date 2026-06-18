#include "Leds.h"
#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

// ---------------------------------------------------------
// DEFINICION DE MACROS
// ---------------------------------------------------------
#define LEDS_PORT 	(uint8_t)0
#define GREEN_1_PIN ((uint32_t)(1<<9))
#define GREEN_2_PIN ((uint32_t)(1<<8))
#define YELLOW_PIN  ((uint32_t)(1<<7))
#define RED_1_PIN  	((uint32_t)(1<<6))
#define RED_2_PIN  	((uint32_t)(1<<0))

// ---------------------------------------------------------
// PROTOTIPOS DE FUNCIONES PRIVADAS
// ---------------------------------------------------------
static void cfgGPIO(void);

// ---------------------------------------------------------
// FUNCIONES PUBLICAS
// ---------------------------------------------------------
void Leds_Init(void) {
	cfgGPIO();
}

void Led_TurnOn(Led_t led) {
    switch(led) {
        case LED_GREEN_1: GPIO_SetValue(LEDS_PORT, GREEN_1_PIN); break;
        case LED_GREEN_2: GPIO_SetValue(LEDS_PORT, GREEN_2_PIN); break;
        case LED_YELLOW:  GPIO_SetValue(LEDS_PORT, YELLOW_PIN); break;
        case LED_RED_1:   GPIO_SetValue(LEDS_PORT, RED_1_PIN); break;
        case LED_RED_2:   GPIO_SetValue(LEDS_PORT, RED_2_PIN); break;
    }
}

void Led_TurnOff(Led_t led) {
    switch(led) {
        case LED_GREEN_1: GPIO_ClearValue(LEDS_PORT, GREEN_1_PIN); break;
        case LED_GREEN_2: GPIO_ClearValue(LEDS_PORT, GREEN_2_PIN); break;
        case LED_YELLOW:  GPIO_ClearValue(LEDS_PORT, YELLOW_PIN); break;
        case LED_RED_1:   GPIO_ClearValue(LEDS_PORT, RED_1_PIN); break;
        case LED_RED_2:   GPIO_ClearValue(LEDS_PORT, RED_2_PIN); break;
    }
}

void Leds_ClearAll(void) {
	GPIO_ClearValue(LEDS_PORT, GREEN_1_PIN);
	GPIO_ClearValue(LEDS_PORT, GREEN_2_PIN);
	GPIO_ClearValue(LEDS_PORT, YELLOW_PIN);
	GPIO_ClearValue(LEDS_PORT, RED_1_PIN);
	GPIO_ClearValue(LEDS_PORT, RED_2_PIN);
}

void Led_Toggle(Led_t led) {
	uint32_t pin_state = GPIO_ReadValue(LEDS_PORT);

	if(pin_state & (1 << led)) {
		Led_TurnOff(led);
	}
	else {
		Led_TurnOn(led);
	}
}

// ---------------------------------------------------------
// DEFINICION DE FUNCIONES PRIVADAS
// ---------------------------------------------------------
void cfgGPIO(void) {
	//-- 1)Estructuras de configuracion --
	//a) Configuracion P0.9 GPIO OUTPUT: LED GREEN_1
	PINSEL_CFG_Type cfgPinLed_GREEN_1;

	//b) Configuracion P0.8 GPIO OUTPUT: LED GREEN_2
	PINSEL_CFG_Type cfgPinLed_GREEN_2;

	//c) Configuracion P0.7 GPIO OUTPUT: LED YELLOW
	PINSEL_CFG_Type cfgPinLed_YELLOW;

	//d) Configuracion P0.6 GPIO OUTPUT: LED RED_1
	PINSEL_CFG_Type cfgPinLed_RED_1;

	//e) Configuracion P0.0 GPIO OUTPUT: LED RED_2
	PINSEL_CFG_Type cfgPinLed_RED_2;

    //-- A)cfgPinLed_GREEN_1 --
	cfgPinLed_GREEN_1.Portnum = PINSEL_PORT_0;
	cfgPinLed_GREEN_1.Pinnum = PINSEL_PIN_9;
	cfgPinLed_GREEN_1.Funcnum = PINSEL_FUNC_0;
	cfgPinLed_GREEN_1.Pinmode = PINSEL_PINMODE_TRISTATE;
	cfgPinLed_GREEN_1.OpenDrain = PINSEL_PINMODE_NORMAL;

    GPIO_SetDir(LEDS_PORT, GREEN_1_PIN, 1);
    GPIO_ClearValue(LEDS_PORT, GREEN_1_PIN);

    //-- B)cfgPinLed_GREEN --
    cfgPinLed_GREEN_2.Portnum = PINSEL_PORT_0;
    cfgPinLed_GREEN_2.Pinnum = PINSEL_PIN_8;
    cfgPinLed_GREEN_2.Funcnum = PINSEL_FUNC_0;
    cfgPinLed_GREEN_2.Pinmode = PINSEL_PINMODE_TRISTATE;
    cfgPinLed_GREEN_2.OpenDrain = PINSEL_PINMODE_NORMAL;

    GPIO_SetDir(LEDS_PORT, GREEN_2_PIN, 1);
    GPIO_ClearValue(LEDS_PORT, GREEN_2_PIN);

    //-- C)cfgPinLed_YELLOW --
    cfgPinLed_YELLOW.Portnum = PINSEL_PORT_0;
    cfgPinLed_YELLOW.Pinnum = PINSEL_PIN_7;
    cfgPinLed_YELLOW.Funcnum = PINSEL_FUNC_0;
    cfgPinLed_YELLOW.Pinmode = PINSEL_PINMODE_TRISTATE;
    cfgPinLed_YELLOW.OpenDrain = PINSEL_PINMODE_NORMAL;

    GPIO_SetDir(LEDS_PORT, YELLOW_PIN, 1);
    GPIO_ClearValue(LEDS_PORT, YELLOW_PIN);

    //-- D)cfgPinLed_RED_1 --
    cfgPinLed_RED_1.Portnum = PINSEL_PORT_0;
    cfgPinLed_RED_1.Pinnum = PINSEL_PIN_6;
    cfgPinLed_RED_1.Funcnum = PINSEL_FUNC_0;
    cfgPinLed_RED_1.Pinmode = PINSEL_PINMODE_TRISTATE;
    cfgPinLed_RED_1.OpenDrain = PINSEL_PINMODE_NORMAL;

    GPIO_SetDir(LEDS_PORT, RED_1_PIN, 1);
    GPIO_ClearValue(LEDS_PORT, RED_1_PIN);

    //-- A)cfgPinLed_RED_2 --
    cfgPinLed_RED_2.Portnum = PINSEL_PORT_0;
    cfgPinLed_RED_2.Pinnum = PINSEL_PIN_0;
    cfgPinLed_RED_2.Funcnum = PINSEL_FUNC_0;
    cfgPinLed_RED_2.Pinmode = PINSEL_PINMODE_TRISTATE;
    cfgPinLed_RED_2.OpenDrain = PINSEL_PINMODE_NORMAL;

    GPIO_SetDir(LEDS_PORT, RED_2_PIN, 1);
    GPIO_ClearValue(LEDS_PORT, RED_2_PIN);

    // -- 2) Inicializacion de cada uno --
    PINSEL_ConfigPin(&cfgPinLed_GREEN_1);
    PINSEL_ConfigPin(&cfgPinLed_GREEN_2);
    PINSEL_ConfigPin(&cfgPinLed_YELLOW);
    PINSEL_ConfigPin(&cfgPinLed_RED_1);
    PINSEL_ConfigPin(&cfgPinLed_RED_2);

    return;
}
