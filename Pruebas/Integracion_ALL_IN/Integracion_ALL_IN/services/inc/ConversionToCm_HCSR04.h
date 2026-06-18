/*******************************************************************//**
* @file	    ConversionToCm_HCSR04.h
* @brief 	Interfaz de conversión de datos para HCSR04
* @details	Define la función para obtener la distancia convertida en centímetros del sensor HCSR04.
* @note		ESW.2.1.5
**********************************************************************/

#ifndef INC_CONVERSIONTOCM_HCSR04_H_
#define INC_CONVERSIONTOCM_HCSR04_H_

#include <stdint.h>
#include <stdbool.h>

/*******************************************************************//**
* @brief 	Obtiene la distancia medida en cm
* @details	Calcula y retorna la distancia del sensor HCSR04 procesando el tiempo del pulso.
* @note		USW.2.1.5.1
**********************************************************************/
uint16_t ConversionToCm_HCSR04_GetDistancia(void);

#endif /* INC_CONVERSIONTOCM_HCSR04_H_ */
