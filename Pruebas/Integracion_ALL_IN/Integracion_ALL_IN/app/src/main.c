#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include "Procesamiento.h"

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
