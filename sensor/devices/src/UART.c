#include "UART.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"

void UART3_Init(void) {
	PINSEL_CFG_Type txd3;
	txd3.Portnum = PINSEL_PORT_0;
	txd3.Pinnum = PINSEL_PIN_25;
	txd3.Funcnum = PINSEL_FUNC_3;
	txd3.Pinmode = PINSEL_PINMODE_PULLUP;
	txd3.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_CFG_Type rxd3;
	rxd3.Portnum = PINSEL_PORT_0;
	rxd3.Pinnum = PINSEL_PIN_26;
	rxd3.Funcnum = PINSEL_FUNC_3;
	rxd3.Pinmode = PINSEL_PINMODE_PULLUP;
	rxd3.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&txd3);
	PINSEL_ConfigPin(&rxd3);

	UART_CFG_Type UARTConfig;
	UART_FIFO_CFG_Type UARTFIFO;

	UART_ConfigStructInit(&UARTConfig);

	UARTConfig.Baud_rate = 115200;

	UART_Init(LPC_UART3, &UARTConfig);
	UART_FIFOConfigStructInit(&UARTFIFO);
	UART_FIFOConfig(LPC_UART3, &UARTFIFO);
	UART_TxCmd(LPC_UART3, ENABLE);
}

void UART3_Transmit(uint8_t *data, uint32_t len) {
	UART_Send(
	LPC_UART3, data, len, BLOCKING);
}

bool UART3_Receive(uint8_t *data) {
	if (UART_GetLineStatus(LPC_UART3) & UART_LSR_RDR) {
		*data = UART_ReceiveByte(LPC_UART3);
		return true;
	}

	return false;
}
