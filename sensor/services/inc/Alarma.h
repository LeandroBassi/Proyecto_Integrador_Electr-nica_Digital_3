#ifndef ALARMA_H
#define ALARMA_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    ESTADO_SISTEMA_APAGADO = 0,
    ESTADO_SISTEMA_SEGURO,      // (Green LEDs, low audio freq)
    ESTADO_SISTEMA_ADVERTENCIA, // (Yellow LEDs, medium audio freq)
    ESTADO_SISTEMA_PELIGRO       // (Red LEDs, high audio freq)
} EstadoSistema_t;

void Alarma_Init(void);
void Alarma_ActualizarInterfaz(EstadoSistema_t estado, uint16_t cms);
void Alarma_ConmutarSilencio(void);
bool Alarma_ComprobarEventoPulsador(void);

#endif /* ALARMA_H */
