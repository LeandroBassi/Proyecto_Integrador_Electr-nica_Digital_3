#ifndef SENSORHCSR04_H
#define SENSORHCSR04_H

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdint.h>
#include <stdbool.h>

void SensorHCSR04_Init(void);
// Dispara el pulso de 10us para iniciar la medición
void SensorHCSR04_Trigger(void);
// Retorna true si ya terminó de llegar el pulso de rebote (Echo)
bool SensorHCSR04_IsDataReady(void);
// Retorna el ancho del pulso capturado en us
uint32_t SensorHCSR04_GetPulseUs(void);

#endif
