#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>

void UART3_Init(void);
void UART3_Transmit(uint8_t *data, uint32_t len);
bool UART3_Receive(uint8_t *data);

#endif /* UART_H */
