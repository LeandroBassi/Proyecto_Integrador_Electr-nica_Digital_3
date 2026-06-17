/*
 * UART.h
 * Modificado para UART3 No Bloqueante
 */

#ifndef UART_H_
#define UART_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdint.h>
#include <stdbool.h>

// Inicializa la UART3 y sus pines correspondientes
void UART3_Init(void);

// Transmite un buffer de datos de forma no bloqueante
void UART3_Transmit(uint8_t *data, uint32_t len);

// Retorna verdadero si el transmisor está libre para un nuevo envío
bool UART3_IsTxReady(void);

// Recibe un byte por polling (opcional, si querés hacerlo por interrupción lo cambiamos)
bool UART3_Receive(uint8_t *data);

#endif /* UART_H_ */
