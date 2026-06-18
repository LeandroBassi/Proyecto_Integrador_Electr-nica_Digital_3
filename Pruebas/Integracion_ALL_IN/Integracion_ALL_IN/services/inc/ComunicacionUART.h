/*
 * ComunicacionUART.h
 * Capa de Servicios - Interfaz de comunicación lógica
 */

#ifndef SERVICES_INC_COMUNICACIONUART_H_
#define SERVICES_INC_COMUNICACIONUART_H_

#include <stdint.h>

// Envía el valor de distancia medido de manera no bloqueante
void ComunicacionUART_EnviarDistancias(uint8_t distancia_sharp, uint16_t distancia_HCSR04);

#endif /* SERVICES_INC_COMUNICACIONUART_H_ */
