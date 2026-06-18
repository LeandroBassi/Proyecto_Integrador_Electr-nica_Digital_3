/*******************************************************************//**
* @file	    TimeService.h
* @brief 	Interfaz del servicio de tiempo
* @details	Gestiona la base de tiempo del sistema y ofrece funciones para control de timeouts.
* @note		ESW.2.1.7
**********************************************************************/

#ifndef SERVICES_INC_TIMESERVICE_H_
#define SERVICES_INC_TIMESERVICE_H_

#include <stdint.h>
#include <stdbool.h>

/*******************************************************************//**
* @brief 	Inicializa el servicio de tiempo
* @details	Configura los recursos necesarios para la gestión de tiempo (ej. SysTick).
* @note		USW.2.1.7.1
**********************************************************************/
void TimeService_Init(void);

/*******************************************************************//**
* @brief 	Verifica y limpia un timeout
* @details	Retorna 'true' si ha transcurrido el intervalo especificado desde la última verificación.
* @note		USW.2.1.7.2
**********************************************************************/
bool TimeService_CheckAndClearTimeout(uint32_t ms_interval);

/*******************************************************************//**
* @brief 	Obtiene los ticks actuales
* @details	Retorna el contador de milisegundos transcurridos desde el inicio.
* @note		USW.2.1.7.3
**********************************************************************/
uint32_t TimeService_GetTicks(void);

#endif /* SERVICES_INC_TIMESERVICE_H_ */
