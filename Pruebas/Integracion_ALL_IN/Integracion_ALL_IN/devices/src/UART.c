/*******************************************************************//**
* @file	    UART.c
* @brief 	Implementación del dispositivo UART
* @details	Configura la UART3 para comunicación serie no bloqueante mediante interrupciones.
* @note		ESW.2.1.13
**********************************************************************/

#include "UART.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"

//----------------------------------------------------------------
// Bandera interna para controlar si el periférico está transmitiendo
static volatile bool tx_busy = false;

/*******************************************************************//**
* @brief 	Configura los pines GPIO para UART3
* @details	Configura los registros PINSEL para los pines TX y RX de la UART3.
* @note		USW.2.1.13.5
**********************************************************************/
static void cfgGPIO(void);

/*******************************************************************//**
* @brief 	Configura la UART3
* @details	Configura el baudrate, FIFO e interrupciones de la UART3.
* @note		USW.2.1.13.6
**********************************************************************/
static void cfgUART(void);
//----------------------------------------------------------------

/*******************************************************************//**
* @brief 	Inicializa la UART3
* @details	Configura los pines y los parámetros de comunicación de la UART3.
* @note		USW.2.1.13.1
**********************************************************************/
void UART3_Init(void) {
    cfgGPIO();
    cfgUART();
}

/*******************************************************************//**
* @brief 	Transmite datos por UART
* @details	Transmite un buffer de datos de forma no bloqueante.
* @note		USW.2.1.13.2
**********************************************************************/
void UART3_Transmit(uint8_t *data, uint32_t len) {
    // Solo enviamos si el hardware no está ocupado
    if (!tx_busy) {
        tx_busy = true; // Levantamos la bandera
        // Usamos NONE_BLOCKING para que la CPU no se quede esperando
        UART_Send(LPC_UART3, data, len, NONE_BLOCKING);
    }
}

/*******************************************************************//**
* @brief 	Verifica disponibilidad del transmisor
* @details	Retorna verdadero si el transmisor está libre para un nuevo envío.
* @note		USW.2.1.13.3
**********************************************************************/
bool UART3_IsTxReady(void) {
    return !tx_busy;
}

/*******************************************************************//**
* @brief 	Recibe datos por UART
* @details	Recibe un byte por polling.
* @note		USW.2.1.13.4
**********************************************************************/
bool UART3_Receive(uint8_t *data) {
    if (UART_GetLineStatus(LPC_UART3) & UART_LSR_RDR) {
        *data = UART_ReceiveByte(LPC_UART3);
        return true;
    }
    return false;
}

//----------------------------------------------------------------
static void cfgGPIO(void) {
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
}

static void cfgUART(void) {
    UART_CFG_Type UARTConfig;
    UART_FIFO_CFG_Type UARTFIFO;

    UART_ConfigStructInit(&UARTConfig);
    UARTConfig.Baud_rate = 115200;

    UART_Init(LPC_UART3, &UARTConfig);

    UART_FIFOConfigStructInit(&UARTFIFO);
    UART_FIFOConfig(LPC_UART3, &UARTFIFO);

    // Habilitar interrupción por fin de transmisión (Transmitter Holding Register Empty)
    UART_IntConfig(LPC_UART3, UART_INTCFG_THRE, ENABLE);

    UART_TxCmd(LPC_UART3, ENABLE);

    // Habilitar la interrupción de la UART3 en el NVIC (Controlador de Interrupciones Vectorizado)
    NVIC_SetPriority(UART3_IRQn, 2);
    NVIC_EnableIRQ(UART3_IRQn);
}

/*******************************************************************//**
* @brief 	Handler de la interrupción de la UART3
* @details	Gestiona el evento de transmisión completada para liberar la bandera de ocupado.
* @note		USW.2.1.13.7
**********************************************************************/
void UART3_IRQHandler(void) {
    // Identificamos la causa de la interrupción leyendo el IIR
    uint32_t intsrc = LPC_UART3->IIR;
    uint32_t intid = (intsrc >> 1) & 0x07;

    // 0x01 corresponde a la interrupción THRE (Transmisor vacío)
    if (intid == 0x01) {
        tx_busy = false; // La transmisión terminó, liberamos la bandera
    }
}
