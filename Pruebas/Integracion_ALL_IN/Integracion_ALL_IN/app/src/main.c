/*******************************************************************//**
* @file	    main.c
* @brief 	Archivo principal del sistema
* @details	Punto de entrada de la aplicación que gestiona la inicialización y el loop principal.
* @note		ESW.2.1.1
**********************************************************************/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include "Procesamiento.h"

/*******************************************************************//**
* @brief 	Función principal del sistema
* @details	Inicializa los componentes y ejecuta el loop principal.
* @note		USW.2.1.1.1
**********************************************************************/
int main(void) {
    // 1) Inicialización de la Arquitectura de Software
	Procesamiento_Init();

    // 2) Super Lazo
    while(1) {
        // Actualizacion lógica principal del sistema
        Procesamiento_Update();
    }

    return 0;
}
