/*******************************************************************//**
* @file	    Procesamiento.h
* @brief 	Módulo de procesamiento principal
* @details	Define las interfaces para inicializar y actualizar la lógica del sistema.
* @note		ESW.2.1.2
**********************************************************************/

#ifndef PROCESAMIENTO_H
#define PROCESAMIENTO_H

#include <stdint.h>
#include <stdbool.h>

/*******************************************************************//**
* @brief 	Inicializa el módulo de procesamiento
* @details	Configura los recursos necesarios para el procesamiento de datos.
* @note		USW.2.1.2.1
**********************************************************************/
void Procesamiento_Init(void);

/*******************************************************************//**
* @brief 	Actualiza el estado del procesamiento
* @details	Ejecuta el ciclo de actualización de la lógica de procesamiento.
* @note		USW.2.1.2.2
**********************************************************************/
void Procesamiento_Update(void);

#endif /* PROCESAMIENTO_H */
