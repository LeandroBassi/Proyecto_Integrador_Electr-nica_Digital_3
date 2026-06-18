#ifndef ALARMA_H_
#define ALARMA_H_

#include <stdint.h>

void Alarma_Init(void);
void Alarma_ToggleMute(void);

// Servicio principal que decide qué prender y parpadear
void Alarma_Update(uint8_t d_sharp, uint16_t d_ultra);

#endif
