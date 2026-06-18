/*******************************************************************//**
* @file	    UART.h
* @brief 	Interfaz del dispositivo UART
* @details	Define la inicialización y funciones para la comunicación serie UART3.
* @note		ESW.2.1.13
**********************************************************************/

#ifndef UART_H_
#define UART_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************//**
* @brief 	Inicializa la UART3
* @details	Configura los pines y los parámetros de comunicación de la UART3.
* @note		USW.2.1.13.1
**********************************************************************/
void UART3_Init(void);

/*******************************************************************//**
* @brief 	Transmite datos por UART
* @details	Transmite un buffer de datos de forma no bloqueante.
* @note		USW.2.1.13.2
**********************************************************************/
void UART3_Transmit(uint8_t *data, uint32_t len);

/*******************************************************************//**
* @brief 	Verifica disponibilidad del transmisor
* @details	Retorna verdadero si el transmisor está libre para un nuevo envío.
* @note		USW.2.1.13.3
**********************************************************************/
bool UART3_IsTxReady(void);

/*******************************************************************//**
* @brief 	Recibe datos por UART
* @details	Recibe un byte por polling.
* @note		USW.2.1.13.4
**********************************************************************/
bool UART3_Receive(uint8_t *data);

#endif /* UART_H_ */
