/*******************************************************************//**
* @file	    ConversionToCm_Sharp.h
* @brief 	Interfaz de conversión de datos para Sharp
* @details	Define la función para obtener la distancia convertida en centímetros del sensor Sharp.
* @note		ESW.2.1.6
**********************************************************************/

#ifndef CONVERSIONTOCM_SHARP_H_
#define CONVERSIONTOCM_SHARP_H_

#include <stdint.h>

/*******************************************************************//**
* @brief 	Obtiene la distancia medida en cm
* @details	Calcula y retorna la distancia del sensor Sharp a partir de la lectura ADC procesada.
* @note		USW.2.1.6.1
**********************************************************************/
uint8_t ConversionToCm_Sharp_GetDistancia(void);

#endif /* CONVERSIONTOCM_SHARP_H_ */
