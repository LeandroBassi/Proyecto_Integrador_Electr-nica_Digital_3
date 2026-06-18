/*******************************************************************//**
* @file	    ComunicacionUART.c
* @brief 	Implementación del servicio de comunicación UART
* @details	Formatea y transmite los datos de distancia a través de UART.
* @note		ESW.2.1.3
**********************************************************************/

#include "ComunicacionUART.h"
#include "UART.h"

/*******************************************************************//**
* @brief 	Envía las distancias medidas por UART
* @details	Realiza el envío de los datos de los sensores a través de la interfaz UART de forma no bloqueante.
* @note		USW.2.1.3.1
**********************************************************************/
void ComunicacionUART_EnviarDistancias(uint8_t dist_sharp, uint16_t dist_ultra) {
    // Plantilla exacta de 16 caracteres visibles + 1 nulo final = 17 bytes de memoria
    // Índices numéricos: Sharp en [2],[3] y Ultra en [9],[10],[11]
    static char tx_buffer[17] = "S:00cm H:000cm\r\n";

    if (UART3_IsTxReady()) {

        // --- 1. MATEMÁTICA SHARP (2 DÍGITOS) ---
        uint8_t s_decena = dist_sharp / 10;
        uint8_t s_unidad = dist_sharp % 10;

        // --- 2. MATEMÁTICA HCSR04 (3 DÍGITOS) ---
        uint8_t u_centena = dist_ultra / 100;
        uint8_t u_resto   = dist_ultra % 100;
        uint8_t u_decena  = u_resto / 10;
        uint8_t u_unidad  = u_resto % 10;

        // --- 3. INYECCIÓN EXACTA ---
        tx_buffer[2] = s_decena + '0';
        tx_buffer[3] = s_unidad + '0';

        tx_buffer[9]  = u_centena + '0';
        tx_buffer[10] = u_decena  + '0';
        tx_buffer[11] = u_unidad  + '0';

        // Enviamos EXACTAMENTE los 16 bytes.
        // La FIFO de la LPC1769 se llena al 100%, pero no desborda.
        UART3_Transmit((uint8_t *)tx_buffer, 16);
    }
}
