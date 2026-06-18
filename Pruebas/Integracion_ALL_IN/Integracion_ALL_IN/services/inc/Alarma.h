/*******************************************************************//**
* @file	    Alarma.h
* @brief 	Interfaz del servicio de alarma
* @details	Gestiona el estado y comportamiento de la alarma basada en distancias.
* @note		ESW.2.1.4
**********************************************************************/

#ifndef ALARMA_H_
#define ALARMA_H_

#include <stdint.h>

/*******************************************************************//**
* @brief 	Inicializa el servicio de alarma
* @details	Configura los recursos necesarios para la gestión de alarmas.
* @note		USW.2.1.4.1
**********************************************************************/
void Alarma_Init(void);

/*******************************************************************//**
* @brief 	Alterna el estado de silencio de la alarma
* @details	Cambia el estado actual de silencio del servicio.
* @note		USW.2.1.4.2
**********************************************************************/
void Alarma_ToggleMute(void);

/*******************************************************************//**
* @brief 	Actualiza la lógica de la alarma
* @details	Evalúa las distancias y activa las señales correspondientes.
* @note		USW.2.1.4.3
**********************************************************************/
void Alarma_Update(uint8_t d_sharp, uint16_t d_ultra);

#endif
