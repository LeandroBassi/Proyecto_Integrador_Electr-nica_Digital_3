#ifndef COMUNICACION_H
#define COMUNICACION_H

#include <stdint.h>
#include <stdbool.h>

void Comunicacion_Init(void);
void Comunicacion_TransmitirEstadoActual(uint16_t cms);
bool Comunicacion_RecibirModificacionesPC(uint16_t *nuevo_umbral, bool *solicitud_silencio);
bool Comunicacion_HitoTiempoAlcanzado(uint32_t *cronometro, uint32_t periodo_ms);

#endif /* COMUNICACION_H */
