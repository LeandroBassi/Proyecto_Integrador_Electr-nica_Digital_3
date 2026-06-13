#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>

void UART_Init(void);
void UART_Transmitir(uint8_t *data, uint32_t len);
bool UART_Recibir(uint8_t *data);

#endif /* UART_H */
