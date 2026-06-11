#ifndef UART_H
#define UART_H

#include "LPC17xx.h"

void UART_Init(uint32_t baudrate);
void UART_SendString(const char* str);
uint8_t UART_ReceiveByte(uint8_t* byte);

#endif
