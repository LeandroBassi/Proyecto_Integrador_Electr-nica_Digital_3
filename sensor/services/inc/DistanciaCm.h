#ifndef DISTANCIACM_H
#define DISTANCIACM_H

#include <stdint.h>
#include <stdbool.h>

void DistanciaCm_Init(void);
void DistanciaCm_ProcesarMuestras(void);
uint16_t DistanciaCm_ObtenerUltimaMedida(void);
bool DistanciaCm_HitoTiempoAlcanzado(uint32_t *cronometro, uint32_t periodo_ms);

#endif /* DISTANCIACM_H */
