#include "Buzzer.h"
#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

// ---------------------------------------------------------
// DEFINICION DE MACROS
// ---------------------------------------------------------
#define BUZZER_PORT  (uint8_t)2
#define BUZZER_PIN   ((uint32_t)(1<<13))

// ---------------------------------------------------------
// PROTOTIPOS DE FUNCIONES PRIVADAS
// ---------------------------------------------------------
static void cfgGPIO(void);

// ---------------------------------------------------------
// FUNCIONES PUBLICAS
// ---------------------------------------------------------
void Buzzer_Init(void) {
    cfgGPIO();
}

void Buzzer_Set(bool state) {
    if (state) {
        GPIO_SetValue(BUZZER_PORT, BUZZER_PIN);
    } else {
        GPIO_ClearValue(BUZZER_PORT, BUZZER_PIN);
    }
}

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

// ---------------------------------------------------------
// DEFINICION DE FUNCIONES PRIVADAS
// ---------------------------------------------------------
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
