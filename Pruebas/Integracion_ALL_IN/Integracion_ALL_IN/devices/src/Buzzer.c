/*******************************************************************//**
* @file	 Buzzer.c
* @brief 	Implementación del dispositivo Buzzer
* @details	Realiza la configuración del pin GPIO y ofrece las funciones de control para el buzzer.
* @note		ESW.2.1.9
**********************************************************************/

#include "Buzzer.h"
#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

// ---------------------------------------------------------
// DEFINICION DE MACROS
// ---------------------------------------------------------
#define BUZZER_PORT  (uint8_t)2
#define BUZZER_PIN   ((uint32_t)(1<<13))

/*******************************************************************//**
* @brief 	Configura los pines GPIO para el Buzzer
* @details	Configura los registros PINSEL y direcciones GPIO para el pin del buzzer.
* @note		USW.2.1.9.4
**********************************************************************/
static void cfgGPIO(void);

/*******************************************************************//**
* @brief 	Inicializa el módulo Buzzer
* @details	Configura el pin GPIO asociado al buzzer.
* @note		USW.2.1.9.1
**********************************************************************/
void Buzzer_Init(void) {
    cfgGPIO();
}

/*******************************************************************//**
* @brief 	Configura el estado del buzzer
* @details	Enciende o apaga el estado base del buzzer.
* @note		USW.2.1.9.2
**********************************************************************/
void Buzzer_Set(bool state) {
    if (state) {
        GPIO_SetValue(BUZZER_PORT, BUZZER_PIN);
    } else {
        GPIO_ClearValue(BUZZER_PORT, BUZZER_PIN);
    }
}

/*******************************************************************//**
* @brief 	Alterna el estado del buzzer
* @details	Invierte el estado actual del pin.
* @note		USW.2.1.9.3
**********************************************************************/
void Buzzer_Toggle(void) {
    // Leemos el estado actual de los pines en el Puerto 0
    uint32_t estado_actual = GPIO_ReadValue(BUZZER_PORT);

    // Si el bit del pin del buzzer está en alto, lo bajamos. Si no, lo subimos.
    if (estado_actual & BUZZER_PIN) {
        GPIO_ClearValue(BUZZER_PORT, BUZZER_PIN);
    } else {
        GPIO_SetValue(BUZZER_PORT, BUZZER_PIN);
    }
}

static void cfgGPIO(void) {
	// a) Configuración PIN P2.13 GPIO OUTPUT
    PINSEL_CFG_Type cfgPinBuzzer;

    cfgPinBuzzer.Portnum = PINSEL_PORT_2;
    cfgPinBuzzer.Pinnum = PINSEL_PIN_13;
    cfgPinBuzzer.Funcnum = PINSEL_FUNC_0;
    cfgPinBuzzer.Pinmode = PINSEL_PINMODE_TRISTATE;
    cfgPinBuzzer.OpenDrain = PINSEL_PINMODE_NORMAL;

    GPIO_SetDir(BUZZER_PORT, BUZZER_PIN, 1);
    GPIO_ClearValue(BUZZER_PORT, BUZZER_PIN);

    PINSEL_ConfigPin(&cfgPinBuzzer);

    return;
}
