/*******************************************************************//**
* @file	    ComunicacionUART.h
* @brief 	Interfaz del servicio de comunicación UART
* @details	Provee funciones para la transmisión de datos de distancia vía UART.
* @note		ESW.2.1.3
**********************************************************************/

#ifndef SERVICES_INC_COMUNICACIONUART_H_
#define SERVICES_INC_COMUNICACIONUART_H_

#include <stdint.h>

/*******************************************************************//**
* @brief 	Envía las distancias medidas por UART
* @details	Realiza el envío de los datos de los sensores a través de la interfaz UART de forma no bloqueante.
* @note		USW.2.1.3.1
**********************************************************************/
void ComunicacionUART_EnviarDistancias(uint8_t distancia_sharp, uint16_t distancia_HCSR04);

#endif /* SERVICES_INC_COMUNICACIONUART_H_ */
