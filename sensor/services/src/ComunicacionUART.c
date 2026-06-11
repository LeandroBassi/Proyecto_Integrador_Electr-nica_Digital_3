#include "ComunicacionUART.h"

#define UART_RX_BUF_SIZE 64
static volatile uint8_t rx_buffer[UART_RX_BUF_SIZE];
static volatile uint16_t rx_head = 0;
static volatile uint16_t rx_tail = 0;

void UART_Init(uint32_t baudrate) {
    LPC_PINCON->PINSEL1 &= ~((3 << 18) | (3 << 20));
    LPC_PINCON->PINSEL1 |= ((3 << 18) | (3 << 20));

    LPC_SC->PCONP |= (1 << 25);
    LPC_UART3->LCR = (1 << 7) | 3;
    uint32_t dValue = 25000000 / (16 * baudrate);
    LPC_UART3->DLL = dValue & 0xFF;
    LPC_UART3->DLM = (dValue >> 8) & 0xFF;
    LPC_UART3->LCR &= ~(1 << 7);
    LPC_UART3->FCR = 1 | (1 << 1) | (1 << 2);
    LPC_UART3->IER = 1;
    NVIC_EnableIRQ(UART3_IRQn);
}

void UART3_IRQHandler(void) {
    while (LPC_UART3->LSR & 0x01) {
        uint8_t byte = LPC_UART3->RBR;
        uint16_t next_head = (rx_head + 1) % UART_RX_BUF_SIZE;
        if (next_head != rx_tail) {
            rx_buffer[rx_head] = byte;
            rx_head = next_head;
        }
    }
}

void UART_SendString(const char* str) {
    while (*str) {
        while (!(LPC_UART3->LSR & (1 << 5)));
        LPC_UART3->THR = *str++;
    }
}

uint8_t UART_ReceiveByte(uint8_t* byte) {
    if (rx_head == rx_tail) return 0;
    *byte = rx_buffer[rx_tail];
    rx_tail = (rx_tail + 1) % UART_RX_BUF_SIZE;
    return 1;
}
