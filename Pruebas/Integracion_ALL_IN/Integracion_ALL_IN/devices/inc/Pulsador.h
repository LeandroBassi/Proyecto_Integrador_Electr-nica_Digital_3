/*******************************************************************//**
* @file	    Pulsador.h
* @brief 	Interfaz del dispositivo Pulsador
* @details	Define la inicialización para el manejo de interrupciones externas del pulsador.
* @note		ESW.2.1.10
**********************************************************************/

#ifndef PULSADOR_H
#define PULSADOR_H

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdbool.h>

/*******************************************************************//**
* @brief 	Inicializa el módulo Pulsador
* @details	Configura los pines y las interrupciones externas asociadas al pulsador.
* @note		USW.2.1.10.1
**********************************************************************/
void Pulsador_Init(void);

#endif /* PULSADOR_H */
