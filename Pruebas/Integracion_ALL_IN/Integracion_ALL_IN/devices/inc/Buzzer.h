/*******************************************************************//**
* @file	 Buzzer.h
* @brief 	Interfaz del dispositivo Buzzer
* @details	Define las funciones para controlar el buzzer del sistema.
* @note		ESW.2.1.9
**********************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdbool.h>

/*******************************************************************//**
* @brief 	Inicializa el módulo Buzzer
* @details	Configura el pin GPIO asociado al buzzer.
* @note		USW.2.1.9.1
**********************************************************************/
void Buzzer_Init(void);

/*******************************************************************//**
* @brief 	Configura el estado del buzzer
* @details	Enciende o apaga el estado base del buzzer.
* @note		USW.2.1.9.2
**********************************************************************/
void Buzzer_Set(bool state);

/*******************************************************************//**
* @brief 	Alterna el estado del buzzer
* @details	Invierte el estado actual del pin.
* @note		USW.2.1.9.3
**********************************************************************/
void Buzzer_Toggle(void);

#endif /* BUZZER_H_ */
