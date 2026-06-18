/*******************************************************************//**
* @file	 SensorSharp.h
* @brief 	Interfaz del sensor Sharp
* @details	Define la inicialización y funciones para obtener lecturas del sensor Sharp.
* @note		ESW.2.1.11
**********************************************************************/

#ifndef SENSORSHARP_H_
#define SENSORSHARP_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

/*******************************************************************//**
* @brief 	Inicializa el sensor Sharp
* @details	Configura los periféricos necesarios para la lectura del sensor (GPIO, ADC, DMA, TIMER).
* @note		USW.2.1.11.1
**********************************************************************/
void SensorSharp_Init(void);

/*******************************************************************//**
* @brief 	Obtiene el valor promedio del sensor
* @details	Retorna el valor crudo (0-4095) promediado mediante DMA.
* @note		USW.2.1.11.2
**********************************************************************/
uint16_t SensorSharp_GetPromedioCrudo(void);

#endif /* SENSORSHARP_H_ */
