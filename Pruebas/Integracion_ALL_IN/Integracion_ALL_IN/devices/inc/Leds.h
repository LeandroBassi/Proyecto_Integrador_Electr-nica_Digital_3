/*******************************************************************//**
* @file	 Leds.h
* @brief 	Interfaz del dispositivo de LEDs
* @details	Define las funciones para controlar los LEDs del sistema.
* @note		ESW.2.1.8
**********************************************************************/

#ifndef LEDS_H
#define LEDS_H

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdint.h>
#include <stdbool.h>

typedef enum {
	LED_GREEN_1 = 9,
	LED_GREEN_2 = 8,
    LED_YELLOW = 7,
    LED_RED_1 = 6,
	LED_RED_2 = 0
} Led_t;

/*******************************************************************//**
* @brief 	Inicializa el módulo de LEDs
* @details	Configura los pines GPIO para los LEDs.
* @note		USW.2.1.8.1
**********************************************************************/
void Leds_Init(void);

/*******************************************************************//**
* @brief 	Enciende un LED
* @details	Activa el pin correspondiente al LED seleccionado.
* @note		USW.2.1.8.2
**********************************************************************/
void Led_TurnOn(Led_t led);

/*******************************************************************//**
* @brief 	Apaga un LED
* @details	Desactiva el pin correspondiente al LED seleccionado.
* @note		USW.2.1.8.3
**********************************************************************/
void Led_TurnOff(Led_t led);

/*******************************************************************//**
* @brief 	Apaga todos los LEDs
* @details	Desactiva todos los pines GPIO configurados como LEDs.
* @note		USW.2.1.8.4
**********************************************************************/
void Leds_ClearAll(void);

/*******************************************************************//**
* @brief 	Alterna el estado de un LED
* @details	Cambia el estado actual (On/Off) del pin del LED.
* @note		USW.2.1.8.5
**********************************************************************/
void Led_Toggle(Led_t led);

#endif /* LEDS_H */
