/*******************************************************************//**
* @file	    Alarma.c
* @brief 	Implementación del servicio de alarma
* @details	Define el comportamiento de los indicadores (LEDs/Buzzer) según las distancias recibidas.
* @note		ESW.2.1.4
**********************************************************************/

#include "Alarma.h"
#include "Leds.h"
#include "Buzzer.h"
#include "TimeService.h"
#include <stdbool.h>

//DISTANCIAS PARA DEFINIR LOS RANGOS:
#define DISTANCIA_MIN 		(uint8_t)10
#define DISTANCIA_MEDIA_1	(uint8_t)25
#define DISTANCIA_MEDIA_2	(uint8_t)40
#define DISTANCIA_MAX 		(uint8_t)80

// ---------------------------------------------------------
// Variable de estado del mute (pulsador)
// ---------------------------------------------------------
static bool is_muted = false;

/*******************************************************************//**
* @brief 	Inicializa el servicio de alarma
* @details	Configura los recursos necesarios para la gestión de alarmas.
* @note		USW.2.1.4.1
**********************************************************************/
void Alarma_Init(void) {
    is_muted = false;
}

/*******************************************************************//**
* @brief 	Alterna el estado de silencio de la alarma
* @details	Cambia el estado actual de silencio del servicio.
* @note		USW.2.1.4.2
**********************************************************************/
void Alarma_ToggleMute(void) {
    is_muted = !is_muted;
    if (is_muted) {
        Buzzer_Set(false); // Apagado de emergencia
    }
}

/*******************************************************************//**
* @brief 	Parpadeo no bloqueante de LEDs
* @details	Alterna el estado de un LED y el buzzer según el tiempo transcurrido.
* @note		USW.2.1.4.4
**********************************************************************/
static void BlinkLeds(Led_t led_activo, uint32_t delay_ms) {
    static uint32_t t_blink = 0;

    // 1. Lógica de Parpadeo No bloqueante usando Ticks independientes
    if ((TimeService_GetTicks() - t_blink) >= delay_ms) {
    	t_blink = TimeService_GetTicks();

    	Led_Toggle(led_activo);

        if (!is_muted) {
            Buzzer_Toggle();
        }
        else {
        	Buzzer_Set(false);
        }
    }
}

/*******************************************************************//**
* @brief 	Actualiza la lógica de la alarma
* @details	Evalúa las distancias y activa las señales correspondientes.
* @note		USW.2.1.4.3
**********************************************************************/
void Alarma_Update(uint8_t d_sharp, uint16_t d_ultra) {
	//CASOS USANDO DISTANCIA CONVERTIDA DEL HC-SR04: d < 10cm && d > 80cm
    // CASO 1: d_ultra menor a 10cm
    if (d_ultra < DISTANCIA_MIN) {
    	Led_TurnOff(LED_GREEN_1);
    	Led_TurnOff(LED_RED_1);
        Led_TurnOn(LED_RED_2);

        if (!is_muted) {
        	Buzzer_Set(true);
        }
        else {
        	Buzzer_Set(false);
        }
    }

    // CASO 2: d_ultra mayor a 80cm
    else if (d_ultra > DISTANCIA_MAX) {
    	Led_TurnOff(LED_RED_2);
    	Led_TurnOff(LED_GREEN_2);
        Led_TurnOn(LED_GREEN_1);
        Buzzer_Set(false);
    }

    //CASOS USANDO DISTANCIA CONVERTIDA DEL SHARP: d >= 10cm && d <= 80cm
	Led_TurnOff(LED_RED_2);
    Led_TurnOff(LED_GREEN_1);

    // CASO 3: d_sharp menor a 25cm
    if (d_sharp < DISTANCIA_MEDIA_1) {
    	Led_TurnOff(LED_GREEN_2);
        Led_TurnOff(LED_YELLOW);

        // Titileo MUY RÁPIDO
        BlinkLeds(LED_RED_1, 100);
    }
    // CASO 3: d_sharp entre 25cm y 40cm
    else if (d_sharp >= DISTANCIA_MEDIA_1 && d_sharp < DISTANCIA_MEDIA_2) {
    	Led_TurnOff(LED_GREEN_2);
    	Led_TurnOff(LED_RED_1);

        // Titileo MEDIO
        BlinkLeds(LED_YELLOW, 250);
    }
    // CASO 3: d_sharp entre 40cm y 80cm
    else if (d_sharp >= DISTANCIA_MEDIA_2 && d_sharp <= DISTANCIA_MAX) {
    	Led_TurnOff(LED_YELLOW);
        Led_TurnOff(LED_RED_1);

        // Titileo LENTO
        BlinkLeds(LED_GREEN_2, 300);
    }
}
