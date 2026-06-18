/*******************************************************************//**
* @file	    SensorHCSR04.h
* @brief 	Interfaz del sensor HCSR04
* @details	Define la inicialización y funciones para obtener lecturas de tiempo del sensor HCSR04.
* @note		ESW.2.1.12
**********************************************************************/

#ifndef SENSORHCSR04_H
#define SENSORHCSR04_H

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************//**
* @brief 	Inicializa el sensor HCSR04
* @details	Configura los pines GPIO y TIMER0 para el manejo del sensor.
* @note		USW.2.1.12.1
**********************************************************************/
void SensorHCSR04_Init(void);

/*******************************************************************//**
* @brief 	Dispara el pulso de inicio
* @details	Genera el pulso de 10us para iniciar la medición del sensor.
* @note		USW.2.1.12.2
**********************************************************************/
void SensorHCSR04_Trigger(void);

/*******************************************************************//**
* @brief 	Verifica si hay datos listos
* @details	Retorna 'true' si se ha completado la captura del pulso Echo.
* @note		USW.2.1.12.3
**********************************************************************/
bool SensorHCSR04_IsDataReady(void);

/*******************************************************************//**
* @brief 	Obtiene el ancho del pulso
* @details	Retorna el ancho del pulso Echo capturado en microsegundos.
* @note		USW.2.1.12.4
**********************************************************************/
uint32_t SensorHCSR04_GetPulseUs(void);

#endif
