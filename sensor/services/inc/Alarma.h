#ifndef ALARMA_H
#define ALARMA_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    SYSTEM_STATE_OFF = 0,
    SYSTEM_STATE_SAFE,      // (Green LEDs, low audio freq)
    SYSTEM_STATE_WARNING,   // (Yellow LEDs, medium audio freq)
    SYSTEM_STATE_DANGER     // (Red LEDs, high audio freq)
} SystemState_t;

void Alarma_Init(void);
void Alarma_ActualizarInterfaz(SystemState_t state, uint16_t cms);
void Alarma_ConmutarSilencio(void);
bool Alarma_ComprobarEventoPulsador(void);

#endif /* ALARMA_H */
